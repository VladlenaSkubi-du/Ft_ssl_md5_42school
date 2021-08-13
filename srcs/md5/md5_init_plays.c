/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_init_plays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 22:58:53 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/13 23:43:18 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static uint32_t	count_T_and_message_block_by_k(uint32_t *message_512bit_block,
					uint32_t k_round_dependent,
					uint32_t round_index)
{
	uint32_t	sum_T_message_by_k;
	uint32_t	T_const_by_index;
	
	T_const_by_index = get_const_table_sin_value(round_index);
	sum_T_message_by_k = message_512bit_block[k_round_dependent]
		+ T_const_by_index;
	return (sum_T_message_by_k);
}

/*
** For @s_shit we need always to get index 1, 2, 3 or 4 according to
** the architecture in the code designed
** For numbers 4, 8, 12, 16 and so on we will have 0 after round_index % 4
** That is why we add +4 to get index 4.
** Because of the Norm I can not send to play_the_round function
** more than 4 arguments. That is why I combine two arguments
** needed for the main formula into one called @sum_T_message_by_k
*/

int	init_first_play_with_16_rounds(uint32_t round_index,
		uint32_t *message_512bit_block)
{
	uint32_t	k_round_dependent;
	uint32_t	sum_T_message_by_k;
	uint32_t	(*F_fun_function)(uint32_t, uint32_t, uint32_t);
	uint32_t	index_from_four_letters;
	uint32_t	s_shift;

	if (round_index + 1 < round_index)
		return (0);
	k_round_dependent = round_index - 1;
	sum_T_message_by_k = count_T_and_message_block_by_k(message_512bit_block,
		k_round_dependent, round_index);
	F_fun_function = md5_fun_first_play;
	index_from_four_letters = round_index % 4;
	if (index_from_four_letters == 0)
		index_from_four_letters += 4;
	s_shift = get_shift_first_play_value(index_from_four_letters);
	play_the_round(
		sum_T_message_by_k,
		s_shift,
		F_fun_function,
		index_from_four_letters);
	return (0);
}

int	init_second_play_with_16_rounds(uint32_t round_index,
		uint32_t *message_512bit_block)
{
	uint32_t	k_round_dependent;
	uint32_t	sum_T_message_by_k;
	uint32_t	(*F_fun_function)(uint32_t, uint32_t, uint32_t);
	uint32_t	index_from_four_letters;
	uint32_t	s_shift;

	if (round_index + 1 < round_index)
		return (0);
	k_round_dependent = ((round_index - 1) * 5 + 1) % 16;
	sum_T_message_by_k = count_T_and_message_block_by_k(message_512bit_block,
		k_round_dependent, round_index);
	F_fun_function = md5_fun_second_play;
	index_from_four_letters = round_index % 4;
	if (index_from_four_letters == 0)
		index_from_four_letters += 4;
	s_shift = get_shift_second_play_value(index_from_four_letters);
	play_the_round(
		sum_T_message_by_k, 
		s_shift,
		F_fun_function,
		index_from_four_letters);
	return (0);
}

int	init_third_play_with_16_rounds(uint32_t round_index,
		uint32_t *message_512bit_block)
{
	uint32_t	k_round_dependent;
	uint32_t	sum_T_message_by_k;
	uint32_t	(*F_fun_function)(uint32_t, uint32_t, uint32_t);
	uint32_t	index_from_four_letters;
	uint32_t	s_shift;

	if (round_index + 1 < round_index)
		return (0);
	k_round_dependent = ((round_index - 1) * 3 + 5) % 16;
	sum_T_message_by_k = count_T_and_message_block_by_k(message_512bit_block,
		k_round_dependent, round_index);
	F_fun_function = md5_fun_third_play;
	index_from_four_letters = round_index % 4;
	if (index_from_four_letters == 0)
		index_from_four_letters += 4;
	s_shift = get_shift_third_play_value(index_from_four_letters);
	play_the_round(
		sum_T_message_by_k,
		s_shift,
		F_fun_function,
		index_from_four_letters);
	return (0);
}

int	init_fourth_play_with_16_rounds(uint32_t round_index,
		uint32_t *message_512bit_block)
{
	uint32_t	k_round_dependent;
	uint32_t	sum_T_message_by_k;
	uint32_t	(*F_fun_function)(uint32_t, uint32_t, uint32_t);
	uint32_t	index_from_four_letters;
	uint32_t	s_shift;

	if (round_index + 1 < round_index)
		return (0);
	k_round_dependent = ((round_index - 1) * 7) % 16;
	sum_T_message_by_k = count_T_and_message_block_by_k(message_512bit_block,
		k_round_dependent, round_index);
	F_fun_function = md5_fun_fourth_play;
	index_from_four_letters = round_index % 4;
	if (index_from_four_letters == 0)
		index_from_four_letters += 4;
	s_shift = get_shift_fourth_play_value(index_from_four_letters);
	play_the_round(
		sum_T_message_by_k,
		s_shift,
		F_fun_function,
		index_from_four_letters);
	return (0);
}