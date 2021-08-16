/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 14:18:08 by rbednar           #+#    #+#             */
/*   Updated: 2021/08/16 11:05:20 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	st_isspace(char c)
{
	if (c == '\t' || c == ' ' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static int	st_isdigit(char c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}

static char	st_toupper(char c)
{
	if (c >= 'a' && c <= 'f')
		return (c - 32);
	return (c);
}

static int	new_norm_ternary_ret(char *str, int i)
{
	if (str[i] <= '9')
		return (str[i] - '0');
	return (st_toupper(str[i]) - 55);
}

int	ft_atoi_base(char *str, int str_base)
{
	int		i;
	int		neg;
	int		ret;

	neg = 1;
	ret = 0;
	i = 0;
	while (st_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!st_isdigit(st_toupper(str[i])))
			return (-1);
		ret *= str_base;
		ret += new_norm_ternary_ret(str, i);
		i++;
	}
	return (ret * neg);
}
