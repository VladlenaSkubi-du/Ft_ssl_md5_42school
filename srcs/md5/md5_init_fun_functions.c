/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_init_fun_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:21:58 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/25 22:15:23 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

uint32_t		md5_fun_first_play(uint32_t x, uint32_t y, uint32_t z)
{
	uint32_t	step1;
	uint32_t	step2;

	step1 = md5_bit_and(x, y);
	step2 = md5_bit_and(~x, z);
	return (md5_bit_or(step1, step2));
}

uint32_t		md5_fun_second_play(uint32_t x, uint32_t y, uint32_t z)
{
	uint32_t	step1;
	uint32_t	step2;

	step1 = md5_bit_and(x, z);
	step2 = md5_bit_and(~z, y);
	return (md5_bit_or(step1, step2));
}

uint32_t		md5_fun_third_play(uint32_t x, uint32_t y, uint32_t z)
{
	uint32_t	step1;

	step1 = md5_bit_xor(x, y);
	return (md5_bit_xor(step1, z));
}

uint32_t		md5_fun_forth_play(uint32_t x, uint32_t y, uint32_t z)
{
	uint32_t	step1;

	step1 = md5_bit_or(~z, x);
	return (md5_bit_xor(y, step1));
}