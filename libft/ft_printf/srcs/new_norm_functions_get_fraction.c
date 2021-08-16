/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_norm_functions_get_fraction.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:35:33 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/09 21:21:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	new_norm_ternary_bit_fraction_len(long exponent)
{
	if (exponent == -1023)
		return (53 + 1022);
	return (53 - exponent);
}

char	new_norm_ternary_fraction_cycle(int i, long b)
{
	if ((1l << i) & b)
		return ('1');
	return ('0');
}

long	new_norm_ternary_bit_fraction_exponent(long exponent)
{
	if (exponent == -1023)
		return (-1022);
	return (exponent);
}

char	new_norm_ternary_integerl_cycle(t_int128 one, int i, t_int128 bl)
{
	if ((one << (63 - i)) & bl)
		return ('1');
	return ('0');
}

char	new_norm_ternary_integer_cycle(int i, long b)
{
	if ((1l << (52 - i)) & b)
		return ('1');
	return ('0');
}
