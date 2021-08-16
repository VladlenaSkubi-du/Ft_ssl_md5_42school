/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prime_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:11:43 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 11:11:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_find_next_prime_num(size_t number)
{
	size_t			next_prime;
	int				flag;

	next_prime = number + 1;
	while (next_prime <= SIZET_MAX && next_prime + 1 > next_prime)
	{
		flag = ft_check_prime_number(next_prime);
		if (flag == 1)
			return (next_prime);
		next_prime++;
	}
	return (1);
}

int	ft_check_prime_number(size_t number)
{
	size_t			j;
	int				flag;

	flag = 1;
	j = 2;
	while (j <= number / 2)
	{
		if (number % j == 0)
		{
			flag = 0;
			break ;
		}
		j++;
	}
	return (flag);
}
