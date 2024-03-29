/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_root.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:01:58 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 11:11:20 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_nb_root(long nb, size_t root)
{
	long	res;

	res = 1;
	if (root == 0)
		res = 1;
	while (root)
	{
		res *= nb;
		root--;
	}
	return (res);
}
