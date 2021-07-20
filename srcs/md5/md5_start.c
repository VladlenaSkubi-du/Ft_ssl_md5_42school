/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:07:56 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/20 21:57:22 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

#include <stdio.h>

static unsigned int leftRotate(unsigned int x, unsigned int n){
    return (x << n) | (x >> (32 - n));
}

static int	md5_full_algo(char *data, size_t data_size)
{
	unsigned int a0, b0, c0, d0, 
             A, B, C, D,
             i, F, g, bufD;
	    // empty string appended with 1 bit and zeroes till it is 512 bytes long as 16 32-bit words
    unsigned int message[16] = {0x41414141, 0x00000080, 0x00000000, 0x00000000,//binary: 100000000000000000000000...
                                0x00000000, 0x00000000, 0x00000000, 0x00000000,// ...0000000000000000000000000000...
                                0x00000000, 0x00000000, 0x00000000, 0x00000000,// ...0000000000000000000000000000...
                                0x00000000, 0x00000000, 0x00000020, 0x00000000};//...0000000000000000000000000000000

    //0x0000003F ("?")
	//diff <(./ft_ssl) <(echo -en '?' | md5)
    //8 + 1 = 9
    //14 * 4 * 8 = 448
	
	unsigned int shiftAmounts[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                                     5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                                     4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                                     6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    unsigned int partsOfSines[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                                     0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                                     0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                                     0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                                     0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                                     0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                                     0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                                     0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                                     0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                                     0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                                     0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                                     0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                                     0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                                     0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                                     0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                                     0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    a0 = 0x67452301;
    b0 = 0xefcdab89;
    c0 = 0x98badcfe;
    d0 = 0x10325476;

    //gotta put this into a loop for each 512-bit chunk
    A = a0;
    B = b0;
    C = c0;
    D = d0;

    for (i=0; i<64; i++){
        if (i < 16){
            F = (B & C) | (~B & D);
            g = i;
        } else if (i >= 16 && i < 32){
            F = (D & B) | (~D & C);
            g = (5*i + 1) % 16;
        } else if (i >= 32 && i < 48){
            F = B ^ C ^ D;
            g = (3*i + 5) % 16;
        } else if (i >= 48){
            F = C ^ (B | ~D);
            g = (7*i) % 16;
        }
        bufD = D;
        D = C;
        C = B;
        B += leftRotate((A + F + partsOfSines[i] + message[g]), shiftAmounts[i]);
        A = bufD;
    }
    a0 += A;
    b0 += B;
    c0 += C;
    d0 += D;
    //end future loop

    printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", a0&0xff, (a0>>8)&0xff, (a0>>16)&0xff, (a0>>24)&0xff, b0&0xff, (b0>>8)&0xff, (b0>>16)&0xff, (b0>>24)&0xff, c0&0xff, (c0>>8)&0xff, (c0>>16)&0xff, (c0>>24)&0xff, d0&0xff, (d0>>8)&0xff, (d0>>16)&0xff, (d0>>24)&0xff);
	return (0);
}
	
static uint32_t *md5_get_64bit_mlength_of_message(uint64_t mlength_bits_original,
					int	uint32_blocks_in_message_add)
{
	uint32_t	*mlength_bits_add;
	int			index_of_byte;
	int			bit;
	uint64_t	i;

	if (mlength_bits_original + 1 < mlength_bits_original)
		return (NULL);
	mlength_bits_add = (uint32_t*)ft_xmalloc(sizeof(uint32_t) * (uint32_blocks_in_message_add + 1));
	index_of_byte = 0;
	i = 0x8000000000000000;
	bit = 0;
	while (i > 0)
	{
		if (mlength_bits_original & i)
		{
			index_of_byte = bit / 32;
			mlength_bits_add[index_of_byte] |= 1UL << (bit % 32);
		}
		i = i / 2;
		bit++;
	}
	ft_putendl("we add 64bit representation:");
	print_bits_as_32uint_string_big_endian(mlength_bits_add, 2);
	// print_bits_as_32uint_big_endian(mlength_bits_add[0]);
	// print_bits_as_32uint_big_endian(mlength_bits_add[1]);
	return (mlength_bits_add);
}

static uint32_t *md5_add_64bit_mlength_to_message(uint32_t *message,
					int mlength_bits_original, 
					int *mlength_bits_padded)
{
	uint32_t	*message_new;
	uint32_t	*mlength_bits_add;
	int			uint32_blocks_in_message_before;
	int			uint32_blocks_in_message_add;

	uint32_blocks_in_message_add = 2; //there are 2 blocks with 32 bits in 64bit representation
	uint32_blocks_in_message_before = (*mlength_bits_padded) / 8 / 4;
	message_new = (uint32_t*)ft_xmalloc(sizeof(uint32_t) *
		(uint32_blocks_in_message_before + uint32_blocks_in_message_add + 1));
	ft_memcpy(message_new, message, uint32_blocks_in_message_before);
	free(message);
	mlength_bits_add = md5_get_64bit_mlength_of_message((uint64_t)mlength_bits_original,
		uint32_blocks_in_message_add);
	if (mlength_bits_add == NULL)
	{
		free(message_new);
		return (NULL);
	}
	ft_memcpy(message_new + uint32_blocks_in_message_before,
		mlength_bits_add, (size_t)uint32_blocks_in_message_add);
			ft_putendl("full message");
			print_bits_as_32uint_string_big_endian(message_new, uint32_blocks_in_message_before + uint32_blocks_in_message_add);
	return (message_new);
}

static uint32_t *md5_make_padded_message(char *data, size_t data_size,
					int mlength_bits_padded)
{
	uint32_t	*message;
	int			uint32_blocks_in_message;
	int			index_of_byte;
	int			index_of_bit;

	uint32_blocks_in_message = mlength_bits_padded / 8 / 4;
				printf("uint8_in_uint32 = %d\n", uint32_blocks_in_message); // = 30 for "echo -n 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' | ./ft_ssl"
	message = (uint32_t*)ft_xmalloc(sizeof(uint32_t) * (uint32_blocks_in_message + 1));
	ft_memcpy(message, data, data_size); //number of bytes to copy;
				print_bits_as_32uint_string_big_endian(message, data_size);
	index_of_byte = data_size / 4;
				ft_putendl("before we add 1 bit:");
				print_bits_as_32uint_big_endian(message[index_of_byte]);
	index_of_bit = ((int)data_size - index_of_byte * 4) * 8;
				ft_putstr("find_index_of_byte = ");
				ft_putnbr(index_of_byte);
				ft_putstr("; find_index_of_bit = ");
				ft_putnbr(index_of_bit);
				ft_putchar('\n');
	message[index_of_byte] |= 1UL << index_of_bit;
				ft_putendl("after we add 1 bit:");
				print_bits_as_32uint_big_endian(message[index_of_byte]);
	return (message);
}

/*
** when we add one we add 1 bit to the end of the message in bits
*/

static int		md5_count_message_length_bits_padded(int mlength_bits_original)
{
	int			mlength_bits_padded;

	mlength_bits_padded = mlength_bits_original + 1;
	while (mlength_bits_padded % 512 != 448)
		mlength_bits_padded++;
	printf("mlength_bits_padded = %u\n", mlength_bits_padded);
	if (mlength_bits_padded < 0)
		return (-1);
	return (mlength_bits_padded);
}

static int		md5_count_message_length_bits(size_t data_size)
{
	int			mlength_bits_original;

	mlength_bits_original = data_size * sizeof(char) * 8;
	printf("mlength_bits_original = %u\n", mlength_bits_original);
	return (mlength_bits_original);
}

int				md5_algorithm_start(char *data, size_t data_size)
{
	uint32_t	*message;
	int			mlength_bits_original;
	int			mlength_bits_padded;
	
	mlength_bits_original = md5_count_message_length_bits(data_size);
	if (mlength_bits_original < 0)
		return (-1);
	mlength_bits_padded = md5_count_message_length_bits_padded(mlength_bits_original);
	if (mlength_bits_padded < 0)
		return (-1);
	message = md5_make_padded_message(data, data_size, mlength_bits_padded);
	if (message == NULL)
		return (-1);
	message = md5_add_64bit_mlength_to_message(message, mlength_bits_original, &mlength_bits_padded);
	if (message == NULL)
		return (-1);
	// md5_full_algo(data, data_size);
	// message = (uint32_t*)ft_xmalloc(sizeof(uint32_t) * mlength_bits); //мы должны один байт uint8 из char записать в виде uint32 или должны все сообщение записать в виде uint32?
	// prepare_512_blocks(data, bit_length);

	// uint32_t le = 0x12345678;
	// uint32_t le = ft_atoi(data);
	// uint32_t be = __builtin_bswap32(le);

	// int		i;
	// i = 0;
	// while (data[i])
	// {
	// 	le = ft_memcpy(message, data + i, 4);
	// 	i = i + 4;
		// printf("Little-endian: 0x%" PRIx32 "\n", le);
    	// printf("Big-endian:    0x%" PRIx32 "\n", be);
	// }
	return (0);
}