/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:36:41 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/21 17:28:49 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

/*
** Here we initialize buffer variables, than save the 512 bit chunk of
** the message needed for each iteration, than make 64 uint32_t words array
** from this 512 bit chunk because it is part of the sha256 algo.
** After we delete this 512 bit chunk and work with 64 uint32_t words
** array. We do the same with each 512 bit chunk (512 bit = 16 uint32_t words)
**
** For debug:
** printf("message_size_uint32 = %zu\n", message_size_uint32);
*/

int				sha256_calculate_hash_by_algo(uint32_t *message,
					size_t message_size_uint32)
{
	size_t		index_of_512bit_block;

	index_of_512bit_block = 0;
	sha256_init_buffer0_variables();
	sha256_init_buffer_variables();
	while (index_of_512bit_block < message_size_uint32)
	{
		sha256_save_buffer_before_block();
		sha256_init_new_message_block_512bit(message + index_of_512bit_block, 16);
		sha256_init_64words_message_block(16);
		sha256_free_new_message_block_512bit();
		sha256_make_message_schedule_64words();
		sha256_compress_64_words_block();
		sha256_save_buffer_after_block();
		index_of_512bit_block += 16;
		sha256_increase_block_number(0);
		sha256_free_64words_message_block();
	}
	sha256_increase_block_number(1);
	return (0);
}

/*
** Argument data_size that funtion gets is a feature
**
** For debug:
** printf("data =%s with %zu\n", data + 1, data_size);
*/

int		sha256_algorithm_start(size_t data_size)
{
	char		*data;
	uint32_t	*message;
	size_t		message_size_uint32;
	size_t		mlength_bits_padded;

	while (1)
	{
		if (data_size == 0)
			data = ssl_get_data_algo(&data_size, 1);
		else
			data = ssl_get_data_algo(&data_size, 0);
		if (data == NULL)
			break ;
		message_size_uint32 = 0;
		mlength_bits_padded = 0;
		message = sha256_prepare_message_for_algo(data + 1, data_size,
			&message_size_uint32, &mlength_bits_padded);
		if (message == NULL)
			return (1);
		sha256_calculate_hash_by_algo(message, message_size_uint32);
		sha256_output_hash();
		free(message);
	}
	return (0);
}
