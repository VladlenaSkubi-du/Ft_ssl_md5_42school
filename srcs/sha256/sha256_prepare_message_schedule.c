/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_prepare_message_schedule.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 21:04:03 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/15 21:33:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"
#include "algorithms.h"

/*
** Formula s0: s0 = (w[i-15] rightrotate 7) xor
** (w[i-15] rightrotate 18) xor
** (w[i-15] rightshift 3)
*/

uint32_t		sha256_find_s0_const(uint32_t *message_64words_block, int i)
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

/*
** Formula s1: s1 = (w[i- 2] rightrotate 17) xor
** (w[i- 2] rightrotate 19) xor
** (w[i- 2] rightshift 10)
*/

uint32_t		sha256_find_s1_const(uint32_t *message_64words_block, int i)
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

/*
** We change each uint32 word from the array starting from 16th:
** w[i] = w[i-16] + s0 + w[i-7] + s1
** This way we add 48 generated words
**
** For debug:
** 	// printf("w1 number = %d\n", message_64words_block[i - 15]);
**	// printf("s0\n");
**	// print_bits_as_32uint_little_endian(s0);
**	// ft_putstr("\n");		
**	// printf("s0 number = %d\n", s0);
**
** 	// printf("s1\n");
**	// print_bits_as_32uint_little_endian(s1);
**	// ft_putstr("\n");		
**	// printf("s1 number= %d\n", s1);
**
**  // message_64words_block = sha256_get_64words_message_block();
**  // printf("full 64 words block after change:\n");
**  // print_bits_as_2_32uint_string_little_endian(message_64words_block, 64);
**	// printf("full 64 words:\n");
**	// for(i = 0; i < 64; i++)
**	// {
**	// 	printf("[%d] - ", message_64words_block[i]);
**	// }
**	// printf("\n");
*/

int				sha256_make_message_schedule_64words(void)
{
	uint32_t	*message_64words_block;
	uint32_t	s0;
	uint32_t	s1;
	uint32_t	uint32_for_change;
	size_t		i;

	i = 16;
	message_64words_block = sha256_get_64words_message_block();
	while (i < SHA256_FULL_NUMBER_OF_WORDS)
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
		sha256_change_64words_message_block(i, uint32_for_change);
		i++;
	}
		// message_64words_block = sha256_get_64words_message_block();
		// printf("full 64 words block after change:\n");
		// print_bits_as_2_32uint_string_little_endian(message_64words_block, 64); //TODO delete
	return (0);
}