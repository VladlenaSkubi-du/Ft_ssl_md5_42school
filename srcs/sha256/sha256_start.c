/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:36:41 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/15 20:40:04 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256_notmine.h"

#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

#include "ft_ssl.h"
#include "sha256.h"
#include "algorithms.h"

static uint32_t	*g_sha256_64words_block;

static int		sha256_change_uint32_word_in_64_uint32_words_block(size_t index,
					uint32_t word_to_change)
{
	g_sha256_64words_block[index] = word_to_change;
		print_bits_as_32uint_little_endian(g_sha256_64words_block[index]);
		ft_putstr("\n");
	return (0);
}

static uint32_t	*sha256_get_64_uint32_words_block(void)
{
	return (g_sha256_64words_block);
}

static int		sha256_free_64_uint32_words_block(void)
{
	free(g_sha256_64words_block);
	g_sha256_64words_block = NULL;
	return (0);
}

static uint32_t	sha256_find_s0_const(uint32_t *message_64words_block, int i)
{
	uint32_t	result;
	uint32_t	first;
	uint32_t	second;

	if (i < 1 || i > SHA256_FULL_NUMBER_OF_WORDS)
		return (0);	
	first = uint32_rotate_right_in_algo(message_64words_block[i - SHA256_s0_index],
			SHA256_s0_first_rotright);
	second = uint32_rotate_right_in_algo(message_64words_block[i - SHA256_s0_index],
			SHA256_s0_second_rotright);
	result = uint32_bit_xor(first, second);		
	first = result;
	second = message_64words_block[i - SHA256_s0_index] >> SHA256_s0_third_shift;
	result = uint32_bit_xor(first, second);
	return (result);
}

static uint32_t	sha256_find_s1_const(uint32_t *message_64words_block, int i)
{
	uint32_t	result;
	uint32_t	first;
	uint32_t	second;

	if (i < 1 || i > SHA256_FULL_NUMBER_OF_WORDS)
		return (0);
	first = uint32_rotate_right_in_algo(message_64words_block[i - SHA256_s1_index],
			SHA256_s1_first_rotright);
	second = uint32_rotate_right_in_algo(message_64words_block[i - SHA256_s1_index],
			SHA256_s1_second_rotright);
	result = uint32_bit_xor(first, second);
	first = result;
	second = message_64words_block[i - SHA256_s1_index] >> SHA256_s1_third_shift;
	result = uint32_bit_xor(first, second);
	return (result);
}

static int		sha256_change_64_uint32_words_block(void)
{
	uint32_t	*message_64words_block;
	uint32_t	s0;
	uint32_t	s1;
	uint32_t	uint32_for_change;
	size_t		i;

	i = 16;
	message_64words_block = sha256_get_64_uint32_words_block();
	while (i < SHA256_FULL_NUMBER_OF_WORDS) //SHA256_FULL_NUMBER_OF_WORDS
	{
	// 		printf("before\n");
	// 		print_bits_as_32uint_little_endian(message_64words_block[i]);
	// 		ft_putstr("\n");
		s0 = sha256_find_s0_const(message_64words_block, (int)i);
			// printf("w1 number = %d\n", message_64words_block[i - 15]);
			// printf("s0\n");
			// print_bits_as_32uint_little_endian(s0);
			// ft_putstr("\n");		
			// printf("s0 number = %d\n", s0);
		s1 = sha256_find_s1_const(message_64words_block, (int)i);
			// printf("s1\n");
			// print_bits_as_32uint_little_endian(s1);
			// ft_putstr("\n");		
			// printf("s1 number= %d\n", s1);
		uint32_for_change = message_64words_block[i - SHA256_word_first_index] +
			s0 +
			message_64words_block[i - SHA256_word_second_index] +
			s1;
		sha256_change_uint32_word_in_64_uint32_words_block(i, uint32_for_change);
		i++;
	}
		//print_bits_as_2_32uint_string_little_endian(message_64words_block, 64); //TODO delete
	return (0);
}

/*
** We copy each uint32_t word into the new buffer with little-endian to
** big-endian order
**
** For debug:
** For little-endian before:
** ft_memcpy(g_sha256_64words_block, message_512bit_block,
** 	block_size * (sizeof(uint32_t)));
*/

static int		sha256_add_48_uint32_words_to_message_block_512bit(size_t block_size)
{
	uint32_t	*message_512bit_block;
	size_t		full_words_number_in_block;
	size_t		uint32_word;
	size_t		uint8_part;

	message_512bit_block = sha256_get_message_512bit_block();
	full_words_number_in_block = SHA256_FULL_NUMBER_OF_WORDS;
	g_sha256_64words_block = (uint32_t*)ft_xmalloc(sizeof(uint32_t) *
		(full_words_number_in_block + 1));
	ft_memcpy(g_sha256_64words_block, message_512bit_block,
		block_size * (sizeof(uint32_t)));
	return (0);
}

static int	sha256_calculate_hash_by_algo(uint32_t *message,
		size_t message_size_uint32)
{
	size_t		index_of_512bit_block;

	index_of_512bit_block = 0;
	sha256_init_buffer0_variables();
	sha256_init_buffer_variables();
	printf("message_size_uint32 = %zu\n", message_size_uint32); //TODO delete
	while (index_of_512bit_block < message_size_uint32)//message_size_uint32
	{
		sha256_save_buffer_before_block();
		sha256_init_new_message_block_512bit(message + index_of_512bit_block, 16);
		sha256_add_48_uint32_words_to_message_block_512bit(16); //я работаю дальше с этим блоком
		sha256_change_64_uint32_words_block();
		//sha256_calculate_with_fun_functions();
		sha256_free_new_message_block_512bit(); //512bit сhunk мне не нужен
		sha256_free_64_uint32_words_block();
		sha256_save_buffer_after_block();
		index_of_512bit_block += 16;
		sha256_increase_block_number();
	}
	return (0);
}

/*
** Argument data_size that funtion gets is a feature
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
		printf("data =%s with %zu\n", data + 1, data_size); //TODO delete
		message_size_uint32 = 0;
		mlength_bits_padded = 0;
		message = sha256_prepare_message_for_algo(data + 1, data_size,
			&message_size_uint32, &mlength_bits_padded);
		if (message == NULL)
			return (1);
			printf("my algo:\n");
		sha256_calculate_hash_by_algo(message, message_size_uint32);
			printf("__________\n");
		// sha256_output_hash();
		free(message);
	}
	//////////////////////////////////////////
	// 	printf("other algo:\n");
	// BYTE text1[] = {"hello world aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};          
	// SHA256_CTX ctx;
	// sha256_init(&ctx);
	// sha256_update(&ctx, text1, strlen(text1));
	//////////////////////////////////////
	return (0);
}
