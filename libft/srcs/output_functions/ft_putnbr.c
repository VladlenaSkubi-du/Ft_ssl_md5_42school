/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:06:06 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 18:21:28 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int		a;
	long	res;

	a = 1;
	res = n;
	if (res < 0)
	{
		res *= -1;
		ft_putchar('-');
	}
	while (a <= res / 10)
		a *= 10;
	while (a != 0)
	{
		ft_putchar(res / a + '0');
		res = res % a;
		a = a / 10;
	}
}
