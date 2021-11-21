/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_calculation_algo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 22:45:25 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/17 14:27:02 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"
#include "algorithms.h"

/*
** Here we init all the variables needed for calculations,
** Save a 512bit part of the message, save variables before
** calculations for this 512bit block
** After calculations we add values abcd variable had before
** the clock calculations started.
*/

int	md5_calculate_hash_by_algo(uint32_t *message,
		size_t message_size_uint32)
{
	size_t		index_of_512bit_block;

	index_of_512bit_block = 0;
	md5_init_buffer0_variables();
	md5_init_buffer_variables();
	while (index_of_512bit_block < message_size_uint32)
	{
		md5_save_buffer_before_block();
		md5_init_new_message_block_512bit(message + index_of_512bit_block, 16);
		md5_calculate_with_fun_functions();
		md5_save_buffer_after_block();
		index_of_512bit_block += 16;
		md5_increase_block_number(0);
		md5_free_new_message_block_512bit();
	}
	md5_increase_block_number(1);
	return (0);
}

/*
** There are 4 fun functions that is why it is easier to
** combine each 16 rounds with 1 fun function in a function
*/

int	md5_calculate_with_fun_functions(void)
{
	uint32_t	*message_512bit_block;
	uint32_t	round_index;

	message_512bit_block = md5_get_message_512bit_block();
	if (message_512bit_block == NULL)
		return (0);
	round_index = 1;
	while (round_index < (MD5_NUMBER_OF_ROUNDS + 1))
	{
		if (round_index >= MD5_first_play_min &&
				round_index <= MD5_first_play_max)
			md5_init_first_play_with_16_rounds(round_index, message_512bit_block);
		else if (round_index >= MD5_second_play_min &&
				round_index <= MD5_second_play_max)
			md5_init_second_play_with_16_rounds(round_index, message_512bit_block);
		else if (round_index >= MD5_third_play_min &&
				round_index <= MD5_third_play_max)
			md5_init_third_play_with_16_rounds(round_index, message_512bit_block);
		else if (round_index >= MD5_fourth_play_min &&
				round_index <= MD5_fourth_play_max)
			md5_init_fourth_play_with_16_rounds(round_index, message_512bit_block);
		round_index++;
	}
	return (0);
}

/*
** Main formula here consist of 3 lines started with aa
** But the point is that each of 4 rounds we change the order
** of the real values saved in aa, bb, cc and dd variables - they
** are usually like: aa not equal a_buffer, bb not equal b_buffer
** and so on.
** Example: first 5 rounds should look like that if we
** write them manually:
** round(a, b, c, d, 0, 7, 1, F);
** round(d, a, b, c, 1, 12, 2, F);
** round(c, d, a, b, 2, 17, 3, F);
** round(b, c, d, a, 3, 22, 4, F);
** round(a, b, c, d, 4, 7, 5, F);
** where the values mean: 
**	round(uint32_t& a,
**      uint32_t b,
**		uint32_t c,
**		uint32_t d,
**		uint32_t k (k_round_dependent),
**		uint32_t s (s_shift),
**		uint32_t i (round_index),
**		uint32_t(*function)(uint32_t, uint32_t, uint32_t))
*/

int	md5_play_the_round(uint32_t sum_T_message_by_k,
		uint32_t s_shift,
		uint32_t (*F_fun_function)(uint32_t, uint32_t, uint32_t),
		uint32_t s_shift_index)
{
	uint32_t	aa;
	uint32_t	bb;
	uint32_t	cc;
	uint32_t	dd;
	char		values_orders_vars[9] = "0abcdabcd";

	if (s_shift_index == 4)
		s_shift_index = 2;
	else if (s_shift_index == 2)
		s_shift_index = 4;
	aa = md5_get_buffer_variables(values_orders_vars[s_shift_index]);
	bb = md5_get_buffer_variables(values_orders_vars[s_shift_index + 1]);
	cc = md5_get_buffer_variables(values_orders_vars[s_shift_index + 2]);
	dd = md5_get_buffer_variables(values_orders_vars[s_shift_index + 3]);
	aa += F_fun_function(bb, cc, dd) + sum_T_message_by_k;
	aa = uint32_rotate_left_in_algo(aa, s_shift);
	aa += bb;
	md5_save_buffer_variables(aa, values_orders_vars[s_shift_index]);
	return (0);
}
