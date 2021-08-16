/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fraction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:14:38 by sbecker           #+#    #+#             */
/*   Updated: 2021/08/09 17:35:08 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*bit_fraction_l(long *exponent_l, t_int128 bl, int *len)
{
	register int	i;
	register int	j;
	t_int128		one;
	char			*b_fraction;

	one = 1;
	*len = new_norm_ternary_bit_fraction_l_len(*exponent_l);
	b_fraction = ft_strnewsetchar(*len, '0');
	if (*exponent_l < 0)
	{
		if (!(bl << 16 != 0 && *exponent_l == -16383))
			b_fraction[*len - 65] = '1';
		i = 64;
		while (--i >= 0)
			b_fraction[*len - 1 - i] = new_norm_ternar_fractl_cycle(one, i, bl);
	}
	else
	{
		j = -1;
		i = *len - 1;
		while (--i >= 0)
			b_fraction[++j] = new_norm_ternar_fractl_cycle(one, i, bl);
	}
	*exponent_l = new_norm_ternary_bit_fraction_l_exponent_l(*exponent_l);
	return (b_fraction);
}

char	*bit_fraction(long *exponent, long b, int *len)
{
	register int	i;
	register int	j;
	char			*b_fraction;

	*len = new_norm_ternary_bit_fraction_len(*exponent);
	b_fraction = ft_memalloc(*len);
	if (*exponent < 0)
	{
		ft_memset((void *)b_fraction, '0', *len - 1);
		if (!(b << 12 != 0 && *exponent == -1023))
			b_fraction[*len - 54] = '1';
		i = 52;
		while (--i >= 0)
			b_fraction[*len - 2 - i] = new_norm_ternary_fraction_cycle(i, b);
	}
	else
	{
		j = -1;
		i = *len - 1;
		while (--i >= 0)
			b_fraction[++j] = new_norm_ternary_fraction_cycle(i, b);
	}
	*exponent = new_norm_ternary_bit_fraction_exponent(*exponent);
	return (b_fraction);
}

void	countup_fraction(t_fcomp *fcomp, int *num, char bit, int *count)
{
	*count = -1;
	if (bit == '1')
	{	
		while (++*count < fcomp->len_fraction)
		{
			fcomp->fraction[*count] += num[*count];
			fcomp->fraction[*count + 1] += fcomp->fraction[*count] / 10;
			fcomp->fraction[*count] %= 10;
		}
	}
	*count = -1;
}

void	get_negative_power(t_fcomp *fcomp, int *num, int i)
{
	int	count;

	count = fcomp->len_fraction - i - 3;
	while (++count < fcomp->len_fraction - 1)
		num[count] = num[count + 1];
	num[fcomp->len_fraction - 1] = 0;
	count = fcomp->len_fraction - i - 3;
	while (++count < fcomp->len_fraction)
		num[count] *= 5;
	count = fcomp->len_fraction - i - 3;
	while (++count < fcomp->len_fraction)
	{
		num[count + 1] += num[count] / 10;
		num[count] %= 10;
	}
}

void	get_fraction(char *b_fraction, t_fcomp *fcomp)
{
	register int	i;
	int				count;
	int				*num;

	fcomp->fraction = (int *)ft_memalloc((fcomp->len_fraction + 1) * 4);
	num = (int *)ft_memalloc((fcomp->len_fraction + 1) * 4);
	num[fcomp->len_fraction - 1] = 5;
	i = -1;
	while (b_fraction[++i])
	{
		countup_fraction(fcomp, num, b_fraction[i], &count);
		get_negative_power(fcomp, num, i);
	}
	free(num);
}
