/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:33:26 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 18:21:00 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printmap(char **map, int side)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < side)
	{
		while (j < side)
		{
			ft_putchar(map[i][j]);
			j++;
		}
		ft_putchar('\n');
		j = 0;
		i++;
	}
}
