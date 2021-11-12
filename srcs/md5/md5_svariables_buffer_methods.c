/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_svariables_buffer_methods.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 21:49:01 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/12 21:47:44 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static uint32_t	g_a0;
static uint32_t	g_b0;
static uint32_t	g_c0;
static uint32_t	g_d0;

static uint32_t	g_a_buffer;
static uint32_t	g_b_buffer;
static uint32_t	g_c_buffer;
static uint32_t	g_d_buffer;

int			init_buffer0_variables(void)
{
	g_a0 = 0x67452301;
	g_b0 = 0xEFCDAB89;
	g_c0 = 0x98BADCFE;
	g_d0 = 0x10325476;
	return (0);
}

int			init_buffer_variables(void)
{
	g_a_buffer = g_a0;
	g_b_buffer = g_b0;
	g_c_buffer = g_c0;
	g_d_buffer = g_d0;
	return (0);
}

int			save_buffer_variables(uint32_t value, int flag)
{
	if (flag == 'a')
		g_a_buffer = value;
	else if (flag == 'b')
		g_b_buffer = value;
	else if (flag == 'c')
		g_c_buffer = value;
	else
		g_d_buffer = value;
	return (0);
}

int			add_to_buffer_variables(uint32_t value, int flag)
{
	if (flag == 'a')
		g_a_buffer += value;
	else if (flag == 'b')
		g_b_buffer += value;
	else if (flag == 'c')
		g_c_buffer += value;
	else
		g_d_buffer += value;
	return (0);
}

uint32_t	get_buffer_variables(int flag)
{
	if (flag == 'a')
		return (g_a_buffer);
	else if (flag == 'b')
		return (g_b_buffer);
	else if (flag == 'c')
		return (g_c_buffer);
	return (g_d_buffer);
}