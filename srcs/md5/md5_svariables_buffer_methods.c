/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_svariables_buffer_methods.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 21:49:01 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/16 20:41:02 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static uint32_t	g_md5_a0;
static uint32_t	g_md5_b0;
static uint32_t	g_md5_c0;
static uint32_t	g_md5_d0;

static uint32_t	g_md5_a_buffer;
static uint32_t	g_md5_b_buffer;
static uint32_t	g_md5_c_buffer;
static uint32_t	g_md5_d_buffer;

int			md5_init_buffer0_variables(void)
{
	g_md5_a0 = 0x67452301;
	g_md5_b0 = 0xEFCDAB89;
	g_md5_c0 = 0x98BADCFE;
	g_md5_d0 = 0x10325476;
	return (0);
}

int			md5_init_buffer_variables(void)
{
	g_md5_a_buffer = g_md5_a0;
	g_md5_b_buffer = g_md5_b0;
	g_md5_c_buffer = g_md5_c0;
	g_md5_d_buffer = g_md5_d0;
	return (0);
}

int			md5_save_buffer_variables(uint32_t value, int flag)
{
	if (flag == 'a')
		g_md5_a_buffer = value;
	else if (flag == 'b')
		g_md5_b_buffer = value;
	else if (flag == 'c')
		g_md5_c_buffer = value;
	else
		g_md5_d_buffer = value;
	return (0);
}

int			add_to_buffer_variables(uint32_t value, int flag)
{
	if (flag == 'a')
		g_md5_a_buffer += value;
	else if (flag == 'b')
		g_md5_b_buffer += value;
	else if (flag == 'c')
		g_md5_c_buffer += value;
	else
		g_md5_d_buffer += value;
	return (0);
}

uint32_t	md5_get_buffer_variables(int flag)
{
	if (flag == 'a')
		return (g_md5_a_buffer);
	else if (flag == 'b')
		return (g_md5_b_buffer);
	else if (flag == 'c')
		return (g_md5_c_buffer);
	return (g_md5_d_buffer);
}