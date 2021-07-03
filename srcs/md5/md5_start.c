/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:07:56 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/03 23:10:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

	#include <inttypes.h>
	#include <stdio.h>
	
int			md5_algorithm_start(char *data, size_t data_size)
{
	int		result;
	uint32_t *message;
	uint32_t mlength_bits;
	
	result = 0;
	printf("data_size = %zu\n", data_size);
	mlength_bits = data_size * sizeof(char) * 8;
	mlength_bits += 1; //добавляем 1 бит
	printf("mlength_bits = %u\n", mlength_bits);
	while (mlength_bits % 512 != 448)
		mlength_bits++;
	printf("mlength_bits = %u\n", mlength_bits);
	message = (uint32_t*)ft_xmalloc(sizeof(uint32_t) * mlength_bits); //мы должны один байт uint8 из char записать в виде uint32 или должны все сообщение записать в виде uint32?
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
	return (result);
}