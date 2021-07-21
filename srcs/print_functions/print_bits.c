/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:04:41 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/21 15:23:48 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "print_functions.h"

static void		char_to_bit(char c)
{
	int			i;
	
	i = 7;
	while (i >= 0)
	{
		ft_putchar_fd((c & (1 << i) ? '1' : '0'), STDOUT_FILENO);
		i--;
	}
	ft_putchar(' ');
}

void			print_bits(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		char_to_bit(str[i]);
		i++;
	}
	char_to_bit('\0');
	ft_putchar('\n');
}

/*
** 0x80000000 is 10000000 00000000 00000000 00000000 or 2 ^ 31
** This way we start to check each index of the memory
** allocated for uint32_t
*/

void			print_bits_as_32uint_little_endian(uint32_t number)
{
	int			bit;
	uint32_t	i;

	i = 0x80000000;
	bit = 0;
	while (i > 0)
	{
		ft_putchar_fd((number & i) ? '1' : '0', STDOUT_FILENO);
		i = i / 2;
		bit++;
		if (bit % 8 == 0)
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

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
	ft_putchar('\n');
}

void		print_bits_as_32uint_string_big_endian(uint32_t *message, int uint32_blocks)
{
	int		i;

	i = 0;
	while (i < uint32_blocks)
	{
		print_bits_as_32uint_big_endian(message[i]);
		i++;
	}
}

void		print_bits_as_32uint_string_little_endian(uint32_t *message, int uint32_blocks)
{
	int		i;

	i = 0;
	while (i < uint32_blocks)
	{
		print_bits_as_32uint_little_endian(message[i]);
		i++;
	}
}