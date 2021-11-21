/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_print_algo_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 21:59:02 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/21 14:44:43 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "print_functions.h"

void			md5_print_message_prepared_in_10(uint32_t *message,
					size_t message_size_uint32)
{
	size_t		i;
	
	i = 0;
	while (i < message_size_uint32)
	{
		ft_printf("%d - ", (int)message[i]);
		i++;
	}
	ft_putchar('\n');
}

void			md5_print_message_prepared(uint32_t *message,
					size_t message_size_uint32,
					size_t mlength_bits_padded)
{
	ft_putstr("full message with message_size_uint32 = ");
	ft_putnbr(message_size_uint32);
	ft_putstr(" and bits padded mlength_bits_padded = ");
	ft_putnbr(mlength_bits_padded);
	ft_putchar('\n');
	print_bits_as_32uint_string_little_endian(message, message_size_uint32);
}