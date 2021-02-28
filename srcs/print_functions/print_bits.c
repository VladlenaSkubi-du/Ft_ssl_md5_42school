/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:04:41 by sschmele          #+#    #+#             */
/*   Updated: 2021/02/28 14:57:08 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "print_functions.h"

static void	char_to_bit(char c)
{
	int		i;
	
	i = 7;
	while (i >= 0)
	{
		ft_putchar((c & (1 << i) ? '1' : '0'));
		i--;
	}
	ft_putchar(' ');
}

void		print_bits(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		char_to_bit(str[i]);
		i++;
	}
	ft_putchar('\n');
}