/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_svariables_block_methods.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:22:48 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/14 01:11:20 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static uint32_t	g_a_before_block;
static uint32_t	g_b_before_block;
static uint32_t	g_c_before_block;
static uint32_t	g_d_before_block;

int			save_buffer_before_block(void)
{
	uint32_t	aa;
	uint32_t	bb;
	uint32_t	cc;
	uint32_t	dd;
	
	aa = get_buffer_variables('a');
	bb = get_buffer_variables('b');
	cc = get_buffer_variables('c');
	dd = get_buffer_variables('d');
	g_a_before_block = aa;
	g_b_before_block = bb;
	g_c_before_block = cc;
	g_d_before_block = dd;
	return (0);
}

int			save_buffer_after_block(void)
{
	add_to_buffer_variables(g_a_before_block, 'a');
	add_to_buffer_variables(g_b_before_block, 'b');
	add_to_buffer_variables(g_c_before_block, 'c');
	add_to_buffer_variables(g_d_before_block, 'd');
	return (0);
}
