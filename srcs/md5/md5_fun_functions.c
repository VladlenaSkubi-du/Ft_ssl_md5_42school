/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fun_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:21:58 by sschmele          #+#    #+#             */
/*   Updated: 2021/03/01 11:30:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

int		ssl_fun_first_play(int x, int y, int z)
{
	int		step1;
	int		step2;

	step1 = ssl_bit_and(x, y);
	step2 = ssl_bit_and(~x, z);
	return (ssl_bit_or(step1, step2));
}

int		ssl_fun_second_play(int x, int y, int z)
{
	int		step1;
	int		step2;

	step1 = ssl_bit_and(x, z);
	step2 = ssl_bit_and(~z, y);
	return (ssl_bit_or(step1, step2));
}

int		ssl_fun_third_play(int x, int y, int z)
{
	int		step1;

	step1 = ssl_bit_xor(x, y);
	return (ssl_bit_xor(step1, z));
}

int		ssl_fun_forth_play(int x, int y, int z)
{
	int		step1;

	step1 = ssl_bit_or(~z, x);
	return (ssl_bit_xor(y, step1));
}