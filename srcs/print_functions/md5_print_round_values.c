/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_print_round_values.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 21:28:30 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/17 14:04:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "print_functions.h"

void		md5_print_description(void)
{
	ft_printf("There are 64 rounds with 4 plays and 16 rounds in it\n");
	ft_printf("Round formula is: a += function(b, c, d) + block[k] + T[i], ");
	ft_printf("a <<<= s, a += b\n");
	ft_printf("    where a, b, c, d - uint32_t buffers,\n");
	ft_printf("    k - uint32_t number dependent on round index,\n");
	ft_printf("    block[k] - uint32_t number from");
	ft_printf(" uint32_t array with length 16 (or 512 bit block),\n");
	ft_printf("    i - uint32_t number from 1 to 64 or round_index\n");
	ft_printf("    T[i] - uint32_t number from the table of constant values\n");
	ft_printf("    s - uint32_t shift dependent on round index,");
	ft_printf(" in each of 4 plays shift values repeat\n");
}

void		md5_print_ksi(uint32_t k_round_dependent,
				uint32_t s_shift_index,
				uint32_t round_index)
{
	uint32_t	*message_block;
	uint32_t	T_const;
	
	message_block = md5_get_message_512bit_block();
	T_const = get_const_table_sin_value(round_index);
	ft_printf("Round %d from 64\n", (int)round_index);
	ft_printf("		k value is %d\n", (int)k_round_dependent);
	ft_printf("		block[k] value is %d\n", (int)message_block[k_round_dependent]);
	ft_printf("		T[i] value is %d\n", (int)T_const);
	ft_printf("		s value is %d\n", (int)s_shift_index);
}

void		md5_print_abcd(void)
{
	uint32_t	aa;
	uint32_t	bb;
	uint32_t	cc;
	uint32_t	dd;

	aa = md5_get_buffer_variables('a');
	bb = md5_get_buffer_variables('b');
	cc = md5_get_buffer_variables('c');
	dd = md5_get_buffer_variables('d');
	ft_printf("We deal with %d 512 bit block from the message\n",
		(int)md5_get_block_number());
	ft_printf("		a value is %d\n", (int)aa);
	ft_printf("		b value is %d\n", (int)bb);
	ft_printf("		c value is %d\n", (int)cc);
	ft_printf("		d value is %d\n", (int)dd);
}