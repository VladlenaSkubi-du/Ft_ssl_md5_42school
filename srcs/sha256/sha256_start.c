/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:36:41 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/16 00:03:07 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256_notmine.h"

#include "ft_ssl.h"
#include "sha256.h"
#include "algorithms.h"

static uint32_t	sha256_find_ch_temp1_algo(void)
{
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	ch_result;
	
	e = sha256_get_buffer_variables('e');
	f = sha256_get_buffer_variables('f');
	g = sha256_get_buffer_variables('g');
	ch_result = uint32_bit_xor(uint32_bit_and(e, f), uint32_bit_and(~e, g));
	return (ch_result);
}

static uint32_t	sha256_find_s1_temp1_algo(void)
{
	uint32_t	first;
	uint32_t	second;
	uint32_t	s1_result;
	uint32_t	e;

	e = sha256_get_buffer_variables('e');
	first = uint32_rotate_right_in_algo(e, SHA256_temp1_s1_efirst_rotright);
	second = uint32_rotate_right_in_algo(e, SHA256_temp1_s1_esecond_rotright);
	s1_result = uint32_bit_xor(first, second);
	first = s1_result;
	second = uint32_rotate_right_in_algo(e, SHA256_temp1_s1_ethird_rotright);
	s1_result = uint32_bit_xor(first, second);
	return (s1_result);
}

static uint32_t	sha256_find_temp1_algo(uint32_t *message_64words_block,
					size_t i)
{
	uint32_t	s1;
	uint32_t	h;
	uint32_t	ch;
	uint32_t	k_const;

	s1 = sha256_find_s1_temp1_algo();
	ch = sha256_find_ch_temp1_algo();
	h = sha256_get_buffer_variables('h');
	k_const = sha256_get_const_table_sin_value(i);
	return (h + s1 + ch + k_const + message_64words_block[i]);
}

static uint32_t	sha256_find_maj_temp2_algo(uint32_t a)
{
	uint32_t	first;
	uint32_t	second;
	uint32_t	maj_result;
	uint32_t	b;
	uint32_t	c;

	b = sha256_get_buffer_variables('b');
	c = sha256_get_buffer_variables('c');
	first = uint32_bit_and(a, b);
	second = uint32_bit_and(a, c);
	maj_result = uint32_bit_xor(first, second);
	first = maj_result;
	second = uint32_bit_and(b, c);
	maj_result = uint32_bit_xor(first, second);
	return (maj_result);
}

static uint32_t	sha256_find_s0_temp2_algo(uint32_t a)
{
	uint32_t	first;
	uint32_t	second;
	uint32_t	s0_result;

	first = uint32_rotate_right_in_algo(a,
		SHA256_temp2_s0_afirst_rotright);
	second = uint32_rotate_right_in_algo(a,
		SHA256_temp2_s0_asecond_rotright);
	s0_result = uint32_bit_xor(first, second);
	first = s0_result;
	second = uint32_rotate_right_in_algo(a,
		SHA256_temp2_s0_athird_rotright);
	s0_result = uint32_bit_xor(first, second);
	return (s0_result);
}

static uint32_t	sha256_find_temp2_algo(void)
{
	uint32_t	s0;
	uint32_t	maj;
	uint32_t	a;

	a = sha256_get_buffer_variables('a');
	s0 = sha256_find_s0_temp2_algo(a);
	maj = sha256_find_maj_temp2_algo(a);
	return (s0 + maj);
}

static int		sha256_compress_64_words_block(void)
{
	uint32_t	*message_64words_block;
	size_t		i;
	uint32_t	temp1;
	uint32_t	temp2;
	
	message_64words_block = sha256_get_64words_message_block();
	i = 0;
	while (i < SHA256_FULL_NUMBER_OF_WORDS)
	{
		temp1 = sha256_find_temp1_algo(message_64words_block, i);
		temp2 = sha256_find_temp2_algo();
		sha256_save_buffer_variables(sha256_get_buffer_variables('g'), 'h');
		sha256_save_buffer_variables(sha256_get_buffer_variables('f'), 'g');
		sha256_save_buffer_variables(sha256_get_buffer_variables('e'), 'f');
		sha256_save_buffer_variables(sha256_get_buffer_variables('d') + temp1, 'e');
		sha256_save_buffer_variables(sha256_get_buffer_variables('c'), 'd');
		sha256_save_buffer_variables(sha256_get_buffer_variables('b'), 'c');
		sha256_save_buffer_variables(sha256_get_buffer_variables('a'), 'b');
		sha256_save_buffer_variables(temp1 + temp2, 'a');
		i++;
	}
	// printf("buffer a is %u\n", sha256_get_buffer_variables('a'));
	return (0);
}

int				sha256_calculate_hash_by_algo(uint32_t *message,
					size_t message_size_uint32)
{
	size_t		index_of_512bit_block;

	index_of_512bit_block = 0;
	sha256_init_buffer0_variables();
	sha256_init_buffer_variables();
	printf("message_size_uint32 = %zu\n", message_size_uint32); //TODO delete
	while (index_of_512bit_block < message_size_uint32) //message_size_uint32
	{
		sha256_save_buffer_before_block();
		sha256_init_new_message_block_512bit(message + index_of_512bit_block, 16);
		sha256_init_64words_message_block(16); //я работаю дальше с этим блоком
		sha256_free_new_message_block_512bit(); //512bit сhunk мне не нужен
		sha256_make_message_schedule_64words();
		sha256_compress_64_words_block();
		sha256_free_64words_message_block();
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
		sha256_output_hash();
		free(message);
	}
	//////////////////////////////////////////
		printf("other algo:\n");
	BYTE text1[] = {"abc"};  
	BYTE hash1[SHA256_BLOCK_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
	        0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};        
	SHA256_CTX ctx;
	BYTE buf[SHA256_BLOCK_SIZE];
	int pass = 1;
	sha256_init(&ctx);
	sha256_update(&ctx, text1, strlen(text1));
	sha256_final(&ctx, buf);
	pass = pass && !memcmp(hash1, buf, SHA256_BLOCK_SIZE);
	printf("SHA-256 tests: %s\n", pass ? "SUCCEEDED" : "FAILED");
	//////////////////////////////////////
	return (0);
}
