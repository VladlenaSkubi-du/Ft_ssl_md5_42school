/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_prepare_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 09:41:38 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/15 20:40:25 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

/*
** Here we create a uint32_t array with the length 2 to write message length
** in bits representation.
** We check each bit from the least significant one because
** numbers are saved in little-endian
** And activate those bits in the string to write the number
** in a uint32_t string
**
** For debug:
** Tried big-endian before
** 	// i = 0x8000000000000000;
**	// bit = 0;
**	// while (i > 0)
**	// {
**	// 	if (mlength_bits_original & i)
**	// 	{
**	// 		index_of_byte = bit / 32;
**	// 		mlength_bits_add[index_of_byte] |= 1UL << (bit % 32);
**	// 	}
**	// 	i = i / 2;
**	// 	bit++;
**	// }
*/

uint32_t 	*md5_get_64bit_mlength_of_message(
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
	i = 0;
	bit = 0;
	while (i < sizeof(mlength_bits_original) * 8)
	{
		if (mlength_bits_original & 1)
		{
			index_of_byte = bit / 32;
			mlength_bits_add[index_of_byte] |= 1UL << (bit % 32);
		}
		i++;
		bit++;
		mlength_bits_original = mlength_bits_original >> 1;
	}
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

uint32_t 	*md5_add_64bit_mlength_to_message(uint32_t *message,
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
	mlength_bits_add = md5_get_64bit_mlength_of_message((uint64_t)mlength_bits_original,
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
** When we count @uint32_blocks_in_message we take the full calculated
** length of the message in bits, divide by 8 to get how many uint8_t
** blocks in the message we should have
** And then divide the final result by 4 because there are 4 uint8_t blocks
** in the uint32_t type
** When we copy the original data to the message array, data_size shows
** the number of bytes to copy
** Function xmalloc allocates memory and puts zeros in it
** That is why we do not need to add zeros in the end - it is already done
** We need to find the place where 1 bit should be activated
** @index_of_byte is needed to find the next byte after the data copied
** @index_of_bit - we need to activate the most significant bit in the byte
** after the data, so: data_size * 8 = the least significant bit after the data
** in the message, data_size * 8 + 7 - the most significant bit after the data
** in the message, (data_size * 8 + 7) % 32 - the most significant bit after the data
** in one block of the message (because it is an array)
**
** For debug:
** printf("uint32_blocks_in_message = %d\n", uint32_blocks_in_message);
** // = 30 for "echo -n
** 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' | ./ft_ssl"
** print_bits_as_32uint_string_little_endian(message, data_size);
** ft_putendl("before we add 1 bit:");
** print_bits_as_32uint_little_endian(message[index_of_byte]);
** 	// ft_putstr("index_of_uint32_block = ");
**	// ft_putnbr(index_of_uint32_block);
**	// ft_putstr("; find_index_of_bit = ");
**	// ft_putnbr(index_of_bit);
**	// ft_putchar('\n');
**  // ft_putendl("after we add 1 bit:");
**	// print_bits_as_32uint_little_endian(message[index_of_byte]);
*/

uint32_t 	*md5_make_padded_message(char *data, size_t data_size,
				size_t *message_size_uint32,
				size_t mlength_bits_padded)
{
	uint32_t	*message;
	size_t		uint32_blocks_in_message;
	size_t		index_of_uint32_block;
	size_t		index_of_bit;

	uint32_blocks_in_message = mlength_bits_padded / 8 / 4;
				// printf("uint32_blocks_in_message = %d\n", uint32_blocks_in_message); // = 30 for "echo -n 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' | ./ft_ssl"
	message = (uint32_t *)ft_xmalloc(sizeof(uint32_t) * (uint32_blocks_in_message + 1));
	ft_memcpy(message, data, sizeof(char) * data_size);
				// print_bits_as_32uint_string_little_endian(message, data_size);
	index_of_uint32_block = data_size / 4;
				// ft_putendl("before we add 1 bit:");
				// print_bits_as_32uint_little_endian(message[index_of_byte]);
	index_of_bit = (data_size * 8 + 7) % 32;
				// ft_putstr("index_of_uint32_block = ");
				// ft_putnbr(index_of_uint32_block);
				// ft_putstr("; find_index_of_bit = ");
				// ft_putnbr(index_of_bit);
				// ft_putchar('\n');
	message[index_of_uint32_block] |= 1UL << index_of_bit;
				// ft_putendl("after we add 1 bit:");
				// print_bits_as_32uint_little_endian(message[index_of_uint32_block]);
	*message_size_uint32 = uint32_blocks_in_message;
	return (message);
}

/*
** When we add one we add 1 bit to the end of the message in bits
** Still not physically, only in our calculations
**
** For debug:
** printf("mlength_bits_padded = %zu\n", mlength_bits_padded);
*/

size_t	md5_count_message_length_bits_padded(size_t mlength_bits_original)
{
	size_t		mlength_bits_padded;

	mlength_bits_padded = mlength_bits_original + 1;
	while (mlength_bits_padded % 512 != 448)
		mlength_bits_padded++;
	return (mlength_bits_padded);
}

/*
** Each char is 1 byte and 8 bits
** But for managing cross-platform ability we count sizeof(char)
**
** For debug:
** printf("mlength_bits_original = %zu\n", mlength_bits_original);
*/

uint32_t	*md5_prepare_message_for_algo(char *data, size_t data_size,
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
	message = md5_add_64bit_mlength_to_message(message, message_size_uint32,
		mlength_bits_original, mlength_bits_padded);
	if (message == NULL)
		return (NULL);
	return (message);
}