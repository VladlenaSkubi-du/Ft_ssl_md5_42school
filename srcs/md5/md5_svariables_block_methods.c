/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_svariables_block_methods.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:22:48 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/16 20:40:10 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static uint32_t	g_md5_a_before_block;
static uint32_t	g_md5_b_before_block;
static uint32_t	g_md5_c_before_block;
static uint32_t	g_md5_d_before_block;

int			md5_save_buffer_before_block(void)
{
	uint32_t	aa;
	uint32_t	bb;
	uint32_t	cc;
	uint32_t	dd;
	
	aa = md5_get_buffer_variables('a');
	bb = md5_get_buffer_variables('b');
	cc = md5_get_buffer_variables('c');
	dd = md5_get_buffer_variables('d');
	g_md5_a_before_block = aa;
	g_md5_b_before_block = bb;
	g_md5_c_before_block = cc;
	g_md5_d_before_block = dd;
	return (0);
}

int			md5_save_buffer_after_block(void)
{
	add_to_buffer_variables(g_md5_a_before_block, 'a');
	add_to_buffer_variables(g_md5_b_before_block, 'b');
	add_to_buffer_variables(g_md5_c_before_block, 'c');
	add_to_buffer_variables(g_md5_d_before_block, 'd');
	return (0);
}
