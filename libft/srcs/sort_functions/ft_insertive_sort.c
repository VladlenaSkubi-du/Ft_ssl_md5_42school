/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertive_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:47:07 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 18:22:40 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(char *str, int dst, int src)
{
	int				temp;

	temp = str[dst];
	str[dst] = str[src];
	str[src] = temp;
}

void	ft_insertive_sort(char *s)
{
	int				i;
	int				step;
	int				len;

	i = 1;
	len = ft_strlen(s);
	while (i < len)
	{
		step = 0;
		while (s[i] > s[i - 1] && s[i])
			i++;
		step = i;
		while ((s[step] <= s[step - 1]) && (step > 0))
		{
			ft_swap(s, step - 1, step);
			step--;
		}
		i++;
	}
}
