/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_init_plays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 22:58:53 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/08 23:00:24 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

/*
** For @s_shit we need always to get index 1, 2, 3 or 4 according to
** the architecture in the code designed
** For numbers 4, 8, 12, 16 and so on we will have 0 after round_index % 4
** That is why we add +4 to get index 4.
*/

int				init_first_play_with_16_rounds(uint32_t round_index)
{
	uint32_t	k_round_dependent;
	uint32_t	s_shift_index;
	uint32_t	(*F_fun_function)(uint32_t, uint32_t, uint32_t);

	if (round_index + 1 < round_index)
		return (0);
	k_round_dependent = round_index - 1;
	s_shift_index = round_index % 4;
	if (s_shift_index == 0)
		s_shift_index += 4;
	F_fun_function = md5_fun_first_play;
	
	play_the_round(
		get_const_table_sin_value(round_index),
		k_round_dependent,
		get_shift_first_play_value(s_shift_index),
		F_fun_function);
				md5_print_ksi(k_round_dependent,
					get_shift_first_play_value(s_shift_index),
					round_index);
	return (0);
}

int				init_second_play_with_16_rounds(uint32_t round_index)
{
	uint32_t	k_round_dependent;
	uint32_t	s_shift_index;
	uint32_t	(*F_fun_function)(uint32_t, uint32_t, uint32_t);

	if (round_index + 1 < round_index)
		return (0);
	k_round_dependent = ((round_index - 1) * 5 + 1) % 16;
	s_shift_index = round_index % 4;
	if (s_shift_index == 0)
		s_shift_index += 4;
	F_fun_function = md5_fun_second_play;
	play_the_round(
		get_const_table_sin_value(round_index),
		k_round_dependent, 
		get_shift_second_play_value(s_shift_index),
		F_fun_function);
				md5_print_ksi(k_round_dependent,
					get_shift_second_play_value(s_shift_index),
					round_index);
	return (0);
}

int				init_third_play_with_16_rounds(uint32_t round_index)
{
	uint32_t	k_round_dependent;
	uint32_t	s_shift_index;
	uint32_t	(*F_fun_function)(uint32_t, uint32_t, uint32_t);

	if (round_index + 1 < round_index)
		return (0);
	k_round_dependent = ((round_index - 1) * 3 + 5) % 16;
	s_shift_index = round_index % 4;
	if (s_shift_index == 0)
		s_shift_index += 4;
	F_fun_function = md5_fun_third_play;
	play_the_round(
		get_const_table_sin_value(round_index),
		k_round_dependent,
		get_shift_third_play_value(s_shift_index),
		F_fun_function);
				md5_print_ksi(k_round_dependent,
					get_shift_third_play_value(s_shift_index),
					round_index);
	return (0);
}

int				init_fourth_play_with_16_rounds(uint32_t round_index)
{
	uint32_t	k_round_dependent;
	uint32_t	s_shift_index;
	uint32_t	(*F_fun_function)(uint32_t, uint32_t, uint32_t);

	if (round_index + 1 < round_index)
		return (0);
	k_round_dependent = ((round_index - 1) * 7) % 16;
	s_shift_index = round_index % 4;
	if (s_shift_index == 0)
		s_shift_index += 4;
	F_fun_function = md5_fun_fourth_play;
	play_the_round(
		get_const_table_sin_value(round_index),
		k_round_dependent,
		get_shift_fourth_play_value(s_shift_index),
		F_fun_function);
				md5_print_ksi(k_round_dependent,
					get_shift_fourth_play_value(s_shift_index),
					round_index);
	return (0);
}