/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_calculation_algo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 22:45:25 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/08 23:00:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

int				md5_calculate_hash_by_algo(uint32_t *message,
					size_t message_size_uint32)
{
	size_t		index_of_512bit_block;

	index_of_512bit_block = 0;
	init_buffer0_variables();
	init_buffer_variables();
	while (index_of_512bit_block < message_size_uint32)
	{
		save_buffer_before_block();
				md5_print_abcd();
		init_new_message_block_512bit(message + index_of_512bit_block, 16);
		calculate_with_fun_functions();
		free_new_message_block_512bit();
		save_buffer_after_block();
				md5_print_abcd();
		index_of_512bit_block += 16;
		increase_block_number();
	}
	return (0);
}

int				calculate_with_fun_functions(void)
{
	uint32_t	round_index;

	round_index = 1;
	while (round_index < (NUMBER_OF_ROUNDS + 1))
	{
		if (round_index >= MD5_first_play_min &&
				round_index <= MD5_first_play_max)
			init_first_play_with_16_rounds(round_index);
		else if (round_index >= MD5_second_play_min &&
				round_index <= MD5_second_play_max)
			init_second_play_with_16_rounds(round_index);
		else if (round_index >= MD5_third_play_min &&
				round_index <= MD5_third_play_max)
			init_third_play_with_16_rounds(round_index);
		else if (round_index >= MD5_fourth_play_min &&
				round_index <= MD5_fourth_play_max)
			init_fourth_play_with_16_rounds(round_index);
		round_index++;
	}
	return (0);
}

static uint32_t	rotate_left_in_play(uint32_t value, uint32_t s_shift)
{
	uint32_t	rotation_done;

	rotation_done = (value << s_shift) |
		(value >> (SIZEOF_UINT32_BIT - s_shift));
	return (rotation_done);
}

int				play_the_round(uint32_t T_const_by_index,
					uint32_t k_round_dependent,
					uint32_t s_shift,
					uint32_t (*F_fun_function)(uint32_t, uint32_t, uint32_t))
{
	uint32_t	*message_512bit_block;
	uint32_t	aa;
	uint32_t	bb;
	uint32_t	cc;
	uint32_t	dd;

	message_512bit_block = get_message_512bit_block();
	aa = get_buffer_variables('a');
	bb = get_buffer_variables('b');
	cc = get_buffer_variables('c');
	dd = get_buffer_variables('d');
	aa += F_fun_function(bb, cc, dd) +
		message_512bit_block[k_round_dependent] +
		T_const_by_index;
	aa = rotate_left_in_play(aa, s_shift);
	aa += bb;
	save_buffer_variables(aa, 'a');
	return (0);
}
