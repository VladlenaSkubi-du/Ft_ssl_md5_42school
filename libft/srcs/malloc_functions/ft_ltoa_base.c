/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:36:05 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 10:53:07 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*new_norm_continuation_str(long nb, int base, int len, char *str)
{
	char			*core;
	int				i;

	core = "0123456789ABCDEF";
	i = 0;
	if (str[0] == '-')
	{
		while (nb)
		{
			str[len - ++i] = core[-(nb % base)];
			nb /= base;
		}
	}
	else
	{
		while (nb)
		{
			str[len - ++i] = core[nb % base];
			nb /= base;
		}
	}
	return (str);
}

static int	count_dig(long value, int base)
{
	int				res;

	res = 0;
	if (value == 0)
		return (1);
	while (value)
	{
		value /= base;
		res++;
	}
	return (res);
}

static char	*ft_ltoa_base_exceptions(long nb)
{
	char			*s;

	s = NULL;
	if (nb == 0)
		return (ft_strdup("0"));
	return (s);
}

char	*ft_ltoa_base(long nb, int base)
{
	char			*str;
	int				len;

	if ((!nb && !base && !(base >= 2 && base <= 16)) || nb == 0)
		return (ft_ltoa_base_exceptions(nb));
	if (nb < 0 && base == 10)
		len = count_dig(nb, base) + 1;
	else
		len = count_dig(nb, base);
	str = (char *)ft_xmalloc(len + 1);
	if (nb < 0)
		str[0] = '-';
	str = new_norm_continuation_str(nb, base, len, str);
	return (str);
}
