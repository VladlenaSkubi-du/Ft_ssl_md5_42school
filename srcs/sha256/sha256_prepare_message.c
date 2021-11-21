/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_prepare_message.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:02:19 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/21 17:10:38 by sschmele         ###   ########.fr       */
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
** print_bits_as_32uint_string_little_endian(mlength_bits_add, 2);
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
		&mlength_bits_add[1], (sizeof(uint32_t) * (uint32_blocks_in_message_add / 2)));
	ft_memcpy(message_new + (*message_size_uint32) + 1,
		&mlength_bits_add[0], (sizeof(uint32_t) * (uint32_blocks_in_message_add / 2)));
	*message_size_uint32 += uint32_blocks_in_message_add;
	*mlength_bits_padded += 64;
	free(mlength_bits_add);
	return (message_new);
}

/*
** Here we copy data bytes as uint8_t bytes info uint32_t word
** For sha256 we need to save all of the bytes as big-endian
**
** For debug:
** 	printf("after change_to_big_endian\n");
**	print_bits_as_32uint_little_endian(message[uint32_word]);
**	ft_putchar('\n');
*/

uint32_t 	*sha256_big_endian_uint32_from_data(char *data, size_t data_size,
				size_t uint32_blocks_in_message)
{
	uint32_t	*message;
	size_t		uint32_data_word_number;
	size_t		uint32_word;
	size_t		uint8_word_part;

	uint32_data_word_number = data_size / 4 + 1;
	message = (uint32_t *)ft_xmalloc(sizeof(uint32_t) * (uint32_blocks_in_message + 1));
	uint32_word = 0;
	uint8_word_part = 0;
	while (uint32_word < uint32_data_word_number)
	{
		message[uint32_word] = (data[uint8_word_part] << 24) | 
			(data[uint8_word_part + 1] << 16) |
			(data[uint8_word_part + 2] << 8) |
			(data[uint8_word_part + 3]);
		uint32_word++;
		uint8_word_part += 4;
	}
	return (message);
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
** after the data, so: data_size * 8 * 4 = the least significant bit after the data
** in the message, data_size * 8 * 4 + 7 - the most significant bit after the data
** in the message, (data_size * 8 * 4 + 7) % 32 - the most significant bit after the data
** in one block of the message (because it is an array)
**
** For debug:
** index_of_uint32_block = 2; find_index_of_bit = 7
** 	printf("uint32_blocks_in_message = %zu\n", uint32_blocks_in_message);
**
**  print_bits_as_32uint_string_little_endian(message, uint32_blocks_in_message);
**
** 	ft_putendl("before we add 1 bit:");
**	print_bits_as_32uint_little_endian(message[index_of_uint32_block]);
**	ft_putchar('\n');
**
** 	ft_putstr("index_of_uint32_block = ");
**	ft_putnbr(index_of_uint32_block);
**	ft_putstr("; find_index_of_bit = ");
**	ft_putnbr(index_of_bit);
**	ft_putchar('\n');
**
** 	ft_putendl("after we add 1 bit:");
**	print_bits_as_32uint_little_endian(message[index_of_uint32_block]);
**	ft_putchar('\n');
**
**	print_bits_as_32uint_string_little_endian(message, uint32_blocks_in_message);
**	ft_putchar('\n');
*/

uint32_t 	*sha256_make_padded_message(char *data, size_t data_size,
				size_t *message_size_uint32,
				size_t mlength_bits_padded)
{
	uint32_t	*message;
	size_t		uint32_blocks_in_message;
	size_t		index_of_uint32_block;
	size_t		index_of_bit;

	uint32_blocks_in_message = mlength_bits_padded / 8 / 4;
	message = sha256_big_endian_uint32_from_data(data, data_size, uint32_blocks_in_message);
	index_of_uint32_block = data_size / 4;
	index_of_bit = 32 - (data_size * 8 % 32) - 1;
	message[index_of_uint32_block] |= 1UL << index_of_bit;
	*message_size_uint32 = uint32_blocks_in_message;
	return (message);
}

/*
** Each char is 1 byte and 8 bits
** But for managing cross-platform ability we count sizeof(char)
**
** For debug:
** printf("mlength_bits_original = %zu\n", mlength_bits_original);
** print_bits_as_32uint_string_little_endian(message, *message_size_uint32);
** 	printf("ready message:\n");
**	int i;
**	for(i = 0; i < 16; i++)
**	{
**		printf("[%d] - ", message[i]);
**	}
**	printf("\n");
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
	message = sha256_make_padded_message(data, data_size,
		message_size_uint32, *mlength_bits_padded);
	if (message == NULL)
		return (NULL);
	message = sha256_add_64bit_mlength_to_message(message, message_size_uint32,
		mlength_bits_original, mlength_bits_padded);
	if (message == NULL)
		return (NULL);
	return (message);
}