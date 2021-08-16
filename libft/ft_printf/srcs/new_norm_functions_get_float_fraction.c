/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_norm_functions_get_float_fraction.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:15:45 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/09 21:21:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	new_norm_ternary_get_components_l_fcomp_sign(t_int128 fcomp_one,
		t_int128 bl)
{
	if ((fcomp_one << 79) & bl)
		return (-1);
	return (1);
}

int	new_norm_ternary_get_components_fcomp_sign(long b)
{
	if ((1lu << 63) & b)
		return (-1);
	return (1);
}

int	new_norm_ternary_bit_fraction_l_len(long exponent_l)
{
	if (exponent_l == -16383)
		return (64 + 16382);
	return (64 - exponent_l);
}

char	new_norm_ternar_fractl_cycle(t_int128 one, int i, t_int128 bl)
{
	if ((one << i) & bl)
		return ('1');
	return ('0');
}

long	new_norm_ternary_bit_fraction_l_exponent_l(long exponent_l)
{
	if (exponent_l == -16383)
		return (-16382);
	return (exponent_l);
}
