////////////////////////////////////////////////

/*********************************************************************
* Filename:   sha256.c

* in main:
* 	//////////////////////////////////////////
		// printf("other algo:\n");
	// BYTE text1[] = {"abc"};  
	// BYTE hash1[SHA256_BLOCK_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
	// //         0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};        
	// BYTE text1[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
	// BYTE hash1[SHA256_BLOCK_SIZE] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
	//                                  0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
	// BYTE text1[] = {"hello world"}; 
	// BYTE hash1[SHA256_BLOCK_SIZE] = {0xb9,0x4d,0x27,0xb9,0x93,0x4d,0x3e,0x08,0xa5,0x2e,0x52,0xd7,0xda,0x7d,0xab,0xfa,
	//                                  0xc4,0x84,0xef,0xe3,0x7a,0x53,0x80,0xee,0x90,0x88,0xf7,0xac,0xe2,0xef,0xcd,0xe9};
	// BYTE text1[] = {"abcde"}; 
	// BYTE hash1[SHA256_BLOCK_SIZE] = {0x36, 0xbb, 0xe5, 0x0e, 0xd9, 0x68, 0x41, 0xd1, 0x04, 0x43, 0xbc, 0xb6, 0x70, 0xd6, 0x55, 0x4f, 
	// 								0x0a, 0x34, 0xb7, 0x61, 0xbe, 0x67, 0xec, 0x9c, 0x4a, 0x8a, 0xd2, 0xc0, 0xc4, 0x4c, 0xa4, 0x2c};
	// SHA256_CTX ctx;
	// BYTE buf[SHA256_BLOCK_SIZE];
	// int pass = 1;
	// sha256_init(&ctx);
	// sha256_update(&ctx, text1, strlen(text1));
	// sha256_final(&ctx, buf);
	// pass = pass && !memcmp(hash1, buf, SHA256_BLOCK_SIZE);
	// printf("SHA-256 tests: %s\n", pass ? "SUCCEEDED" : "FAILED");
	//////////////////////////////////////
*********************************************************************/

/*************************** HEADER FILES ***************************/

#include <stdlib.h>
#include <memory.h>
#include "sha256_notmine.h"
#include "ft_ssl.h"

/****************************** MACROS ******************************/
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

/**************************** VARIABLES *****************************/
static const WORD k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

/*********************** FUNCTION DEFINITIONS ***********************/
void sha256_transform(SHA256_CTX *ctx, const BYTE data[])
{
	WORD a, b, c, d, e, f, g, h, i, j, t1, t2, m[64], print1;

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
	// printf("full 64 words:\n");
	// for(i = 0; i < 16; i++)
	// {
	// 	printf("[%d] - ", m[i]);
	// }
	// printf("\n");
	for ( ; i < 64; ++i)
	{
		// printf("m[1] before = %d\n", m[i - 15]);
		print1 = SIG0(m[i - 15]);
			// printf("s0\n");
			// print_bits_as_32uint_little_endian(print1);
			// ft_putstr("\n");		
			// printf("s0 number = %d\n", print1);
		print1 = SIG1(m[i - 2]);
			// printf("s1\n");
			// print_bits_as_32uint_little_endian(print1);
			// ft_putstr("\n");		
			// printf("s1 number= %d\n", print1);
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
	}
	printf("full 64 words:\n");
	for(i = 0; i < 64; i++)
	{
		printf("[%d] - ", m[i]);
	}
	printf("\n");

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < 64; ++i) {
		//printf("round %i\n", i);
		t1 = h + EP1(e) + CH(e,f,g) + k[i] + m[i];
		// printf("inside t1: h=%u, s1=%u, ch=%u, k[i]=%u, m[i]=%u\n", h, EP1(e), CH(e,f,g), k[i], m[i]);
		//printf("t1 = [%u], ", t1);
		t2 = EP0(a) + MAJ(a,b,c);
		//printf("t2 = [%u], ", t2);
		h = g;
		//printf("h = [%u], ", h);
		g = f;
		//printf("g = [%u], ", g);
		f = e;
		// printf("f = [%u], ", f);
		e = d + t1;
		// printf("e = [%u], ", e);
		d = c;
		// printf("d = [%u], ", d);
		c = b;
		// printf("c = [%u], ", c);
		b = a;
		// printf("b = [%u], ", b);
		a = t1 + t2;
		// printf("a = [%u]\n\n", a);
	}

	// printf("h0 = %u, h1 = %u, h2 = %u, h3 = %u, h4 = %u, h5 = %u, h6 = %u, h7 = %u\n",
	// 	ctx->state[0], ctx->state[1], ctx->state[2], ctx->state[3], ctx->state[4], ctx->state[5], ctx->state[6], ctx->state[7]);

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;

}

void sha256_init(SHA256_CTX *ctx)
{
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}

void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len)
{
	WORD i;

	for (i = 0; i < len; ++i) {
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64) {
			sha256_transform(ctx, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
	}
}

void sha256_final(SHA256_CTX *ctx, BYTE hash[])
{
	WORD i;

	i = ctx->datalen;

	// Pad whatever data is left in the buffer.
	if (ctx->datalen < 56) {
		ctx->data[i++] = 0x80;
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else {
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		sha256_transform(ctx, ctx->data);
		memset(ctx->data, 0, 56);
	}

	// Append to the padding the total message's length in bits and transform.
	ctx->bitlen += ctx->datalen * 8;
	ctx->data[63] = ctx->bitlen;
	ctx->data[62] = ctx->bitlen >> 8;
	ctx->data[61] = ctx->bitlen >> 16;
	ctx->data[60] = ctx->bitlen >> 24;
	ctx->data[59] = ctx->bitlen >> 32;
	ctx->data[58] = ctx->bitlen >> 40;
	ctx->data[57] = ctx->bitlen >> 48;
	ctx->data[56] = ctx->bitlen >> 56;
	sha256_transform(ctx, ctx->data);

	// Since this implementation uses little endian byte ordering and SHA uses big endian,
	// reverse all the bytes when copying the final state to the output hash.
	// printf("h0 = %u, h1 = %u, h2 = %u, h3 = %u, h4 = %u, h5 = %u, h6 = %u, h7 = %u\n",
	// 	ctx->state[0], ctx->state[1], ctx->state[2], ctx->state[3], ctx->state[4], ctx->state[5], ctx->state[6], ctx->state[7]);
	for (i = 0; i < 4; ++i) {
		hash[i]      = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4]  = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8]  = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
	}
}

///////////////////////////////////////////////