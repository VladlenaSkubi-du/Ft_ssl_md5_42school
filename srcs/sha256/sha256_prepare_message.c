/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_prepare_message.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:02:19 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/12 22:21:54 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"
#include "sha256.h"

/*
** Here we create a uint32_t array with the length 2 to write message length
** in bits representation.
** We check each bit from the most significant one because
** numbers are saved in big-endian
** And activate those bits in the string to write the number
** in a uint32_t string
**
** For debug:
*/

uint32_t 	*sha256_get_64bit_mlength_of_message(
				uint64_t mlength_bits_original,
				size_t uint32_blocks_in_message_add)
{
	uint32_t	*mlength_bits_add;
	size_t		index_of_byte;
	size_t		bit;
	uint64_t	i;

	if (mlength_bits_original + 1 < mlength_bits_original)
		return (NULL);
	mlength_bits_add = (uint32_t*)ft_xmalloc(sizeof(uint32_t) *
		(uint32_blocks_in_message_add + 1));
	index_of_byte = 0;
	i = 0x8000000000000000;
	bit = 0;
	while (i > 0)
	{
		if (mlength_bits_original & i)
		{
			index_of_byte = bit / 32;
			mlength_bits_add[index_of_byte] |= 1UL << (bit % 32);
		}	i = i / 2;
		bit++;
	}
		print_bits_as_32uint_string_big_endian(mlength_bits_add, 2);
	return (mlength_bits_add);
}

/*
** @uint32_blocks_in_message_add is equals 2 because
** there are 2 blocks with 32 bits in 64bit representation
** After we allocate new memory for the message with added 64 bit
** Copy the existing message to the new memory
** Free old message
** Create a uint32_t array with the length 2 to write message length
** in bits representation:
** message "A" is 8 bits so representation will be 00001000
** message "AA" is 16 bits so representation will be 00010000
** Copy this array to the new memory after the message
*/

uint32_t 	*sha256_add_64bit_mlength_to_message(uint32_t *message,
				size_t *message_size_uint32,
				size_t mlength_bits_original, 
				size_t *mlength_bits_padded)
{
	uint32_t	*message_new;
	uint32_t	*mlength_bits_add;
	size_t		uint32_blocks_in_message_add;

	uint32_blocks_in_message_add = 2;
	message_new = (uint32_t *)ft_xmalloc(sizeof(uint32_t) *
		(*message_size_uint32 + uint32_blocks_in_message_add + 1));
	ft_memcpy(message_new, message, sizeof(uint32_t) * (*message_size_uint32));
	free(message);
	mlength_bits_add = sha256_get_64bit_mlength_of_message((uint64_t)mlength_bits_original,
		uint32_blocks_in_message_add);
	if (mlength_bits_add == NULL)
	{
		free(message_new);
		return (NULL);
	}
	ft_memcpy(message_new + (*message_size_uint32),
		mlength_bits_add, (sizeof(uint32_t) * uint32_blocks_in_message_add));
	*message_size_uint32 += uint32_blocks_in_message_add;
	*mlength_bits_padded += 64;
	free(mlength_bits_add);
	return (message_new);
}

/*
** Each char is 1 byte and 8 bits
** But for managing cross-platform ability we count sizeof(char)
**
** For debug:
** printf("mlength_bits_original = %zu\n", mlength_bits_original);
*/

uint32_t	*sha256_prepare_message_for_algo(char *data, size_t data_size,
				size_t *message_size_uint32, size_t *mlength_bits_padded)
{
	uint32_t	*message;
	size_t		mlength_bits_original;

	mlength_bits_original = data_size * sizeof(char) * 8;
	if (mlength_bits_original + 1 < mlength_bits_original)
		return (NULL);
	*mlength_bits_padded = md5_count_message_length_bits_padded(mlength_bits_original);
	if (*mlength_bits_padded < 1 || (*mlength_bits_padded + 1 < *mlength_bits_padded))
		return (NULL);
	message = md5_make_padded_message(data, data_size,
		message_size_uint32, *mlength_bits_padded);
	if (message == NULL)
		return (NULL);
		print_bits_as_32uint_string_little_endian(message, *message_size_uint32);
	message = sha256_add_64bit_mlength_to_message(message, message_size_uint32,
		mlength_bits_original, mlength_bits_padded);
	if (message == NULL)
		return (NULL);
	return (message);
}