/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:07:56 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/23 12:24:02 by a18979859        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

/*
** @index_of_512bit_block makes a step of 16 because we need to
** send each 512-bit block where 512 / 8 = 64 bytes or 64 uint8_t blocks
** but 64 / 4 = 16 uint32_t blocks
*/

int		md5_algorithm_start(size_t data_size)
{
	char		*data;
	uint32_t	*message;
	size_t		message_size_uint32;
	size_t		mlength_bits_padded;

	while (1)
	{
		if (data_size == 0)
			data = ssl_get_data(&data_size, 1);
		else
			data = ssl_get_data(&data_size, 0);
		if (data == NULL)
			break ;
		message_size_uint32 = 0;
		mlength_bits_padded = 0;
		message = md5_prepare_message_for_algo(data, data_size,
			&message_size_uint32, &mlength_bits_padded);
		if (message == NULL)
			return (1);
		md5_calculate_hash_by_algo(message, message_size_uint32);
		md5_output_hash();
		free(message);
	}
	return (0);
}