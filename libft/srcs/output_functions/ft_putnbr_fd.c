/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:05:35 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 18:21:25 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	res;
	int		a;

	a = 1;
	res = n;
	if (res < 0)
	{
		res *= -1;
		ft_putchar_fd('-', fd);
	}
	while (a <= res / 10)
		a *= 10;
	while (a != 0)
	{
		ft_putchar_fd(res / a + '0', fd);
		res %= a;
		a /= 10;
	}
}
