/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:07:56 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/25 20:49:54 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

#include <stdio.h>

static unsigned int leftRotate(unsigned int x, unsigned int n){
    return (x << n) | (x >> (32 - n));
}

static int	md5_full_algo(unsigned int *message)
// static int	md5_full_algo(void)
{
	unsigned int a0, b0, c0, d0, 
             A, B, C, D,
             i, F, g, bufD;
	    // empty string appended with 1 bit and zeroes till it is 512 bytes long as 16 32-bit words
    // unsigned int message[16] = {0x00008041, 0x00000000, 0x00000000, 0x00000000,//binary: 100000000000000000000000...
    //                             0x00000000, 0x00000000, 0x00000000, 0x00000000,// ...0000000000000000000000000000...
    //                             0x00000000, 0x00000000, 0x00000000, 0x00000000,// ...0000000000000000000000000000...
    //                             0x00000000, 0x00000000, 0x00000008, 0x00000000};//...0000000000000000000000000000000

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

int				md5_algorithm_start(char *data, size_t data_size)
{
	uint32_t	*message;
	size_t		message_size_uint32;
	size_t		mlength_bits_padded;
	
	// md5_full_algo();
	message_size_uint32 = 0;
	mlength_bits_padded = 0;
	message = md5_prepare_message_for_algo(data, data_size,
		&message_size_uint32, &mlength_bits_padded);
	if (message == NULL)
		return (1);
			// ft_putstr("full message with message_size_uint32 = ");
			// ft_putnbr(message_size_uint32);
			// ft_putstr(" and bits padded mlength_bits_padded = ");
			// ft_putnbr(mlength_bits_padded);
			// ft_putchar('\n');
			// print_bits_as_32uint_string_little_endian(message, message_size_uint32);
	md5_full_algo((unsigned int*)message);

	// size_t i = 0;
	// while (i < message_size_uint32)
	// {
	// 	printf("%d - ", message[i]);
	// 	i++;
	// }
	// printf("\n");
	return (0);
}