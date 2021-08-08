/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_svariables_block_methods.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:22:48 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/08 11:56:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

// static uint32_t	g_a_block;
// static uint32_t	g_b_block;
// static uint32_t	g_c_block;
// static uint32_t	g_d_block;

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

uint32_t	get_buffer_before_block(int flag)
{
	if (flag == 'a')
		return (g_a_before_block);
	else if (flag == 'b')
		return (g_b_before_block);
	else if (flag == 'c')
		return (g_c_before_block);
	return (g_d_before_block);
}

// int			init_block_variables(void)
// {
// 	g_a_block = get_buffer_variables('a');
// 	g_b_block = get_buffer_variables('b');
// 	g_c_block = get_buffer_variables('c');
// 	g_d_block = get_buffer_variables('d');
// 	return (0);
// }

// int			save_block_variable_a(uint32_t a)
// {
// 	g_a_block = a;
// 	return (0);
// }

// uint32_t	get_block_variables(int flag)
// {
// 	if (flag == 'a')
// 		return (g_a_block);
// 	else if (flag == 'b')
// 		return (g_b_block);
// 	else if (flag == 'c')
// 		return (g_c_block);
// 	return (g_d_block);
// }