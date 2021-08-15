/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:07:56 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/14 23:27:03 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

/*
** @index_of_512bit_block makes a step of 16 because we need to
** send each 512-bit block where 512 / 8 = 64 bytes or 64 uint8_t blocks
** but 64 / 4 = 16 uint32_t blocks
*/

int		md5_algorithm_start(void)
{
	char		*data;
	size_t		data_size;
	uint32_t	*message;
	size_t		message_size_uint32;
	size_t		mlength_bits_padded;
	
	data_size = 0;
	data = ssl_get_data(&data_size);
	message_size_uint32 = 0;
	mlength_bits_padded = 0;
	message = md5_prepare_message_for_algo(data, data_size,
		&message_size_uint32, &mlength_bits_padded);
	if (message == NULL)
		return (1);
	md5_calculate_hash_by_algo(message, message_size_uint32);
	md5_output_hash();
	free(message);
	return (0);
}