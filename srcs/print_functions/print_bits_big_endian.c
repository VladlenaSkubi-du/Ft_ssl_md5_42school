/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits_big_endian.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 22:04:28 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/13 23:44:35 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "print_functions.h"

void			print_bits_as_32uint_big_endian(uint32_t number)
{
	int			bit;
	uint32_t	i;

	i = 0;
	bit = 0;
	while (i < sizeof(number) * 8)
	{
		ft_putchar_fd((number & 1) ? '1' : '0', STDOUT_FILENO);
		i++;
		number = number >> 1;
		bit++;
		if (bit % 8 == 0)
			ft_putchar(' ');
	}
}

void		print_bits_as_32uint_string_big_endian(uint32_t *message,
				int uint32_blocks)
{
	int		i;

	i = 0;
	while (i < uint32_blocks)
	{
		print_bits_as_32uint_big_endian(message[i]);
		ft_putchar('\n');
		i++;
	}
}

void		print_bits_as_2_32uint_string_big_endian(uint32_t *message,
				int uint32_blocks)
{
	int		i;

	i = 0;
	while (i < uint32_blocks)
	{
		print_bits_as_32uint_big_endian(message[i]);
		ft_putchar('\t');
		print_bits_as_32uint_big_endian(message[i + 1]);
		ft_putchar('\n');
		i += 2;
	}
}