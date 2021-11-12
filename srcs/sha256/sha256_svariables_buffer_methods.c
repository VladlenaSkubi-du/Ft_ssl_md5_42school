/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_svariables_buffer_methods.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 21:46:38 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/12 22:30:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

static uint32_t	g_sha256_a0;
static uint32_t	g_sha256_b0;
static uint32_t	g_sha256_c0;
static uint32_t	g_sha256_d0;
static uint32_t	g_sha256_e0;
static uint32_t	g_sha256_f0;
static uint32_t	g_sha256_g0;
static uint32_t	g_sha256_h0;

static uint32_t	g_sha256_a_buffer;
static uint32_t	g_sha256_b_buffer;
static uint32_t	g_sha256_c_buffer;
static uint32_t	g_sha256_d_buffer;
static uint32_t	g_sha256_e_buffer;
static uint32_t	g_sha256_f_buffer;
static uint32_t	g_sha256_g_buffer;
static uint32_t	g_sha256_h_buffer;

int			sha256_init_buffer0_variables(void)
{
	g_sha256_a0 = 0x6a09e667;
	g_sha256_b0 = 0xbb67ae85;
	g_sha256_c0 = 0x3c6ef372;
	g_sha256_d0 = 0xa54ff53a;
	g_sha256_e0 = 0x510e527f;
	g_sha256_f0 = 0x9b05688c;
	g_sha256_g0 = 0x1f83d9ab;
	g_sha256_h0 = 0x5be0cd19;
	return (0);
}

int			sha256_init_buffer_variables(void)
{
	g_sha256_a_buffer = g_sha256_a0;
	g_sha256_b_buffer = g_sha256_b0;
	g_sha256_c_buffer = g_sha256_c0;
	g_sha256_d_buffer = g_sha256_d0;
	g_sha256_e_buffer = g_sha256_e0;
	g_sha256_f_buffer = g_sha256_f0;
	g_sha256_g_buffer = g_sha256_g0;
	g_sha256_h_buffer = g_sha256_h0;
	return (0);
}

int			sha256_save_buffer_variables(uint32_t value, int flag)
{
	if (flag == 'a')
		g_sha256_a_buffer = value;
	else if (flag == 'b')
		g_sha256_b_buffer = value;
	else if (flag == 'c')
		g_sha256_c_buffer = value;
	else if (flag == 'd')
		g_sha256_d_buffer = value;
	else if (flag == 'e')
		g_sha256_e_buffer = value;
	else if (flag == 'f')
		g_sha256_f_buffer = value;
	else if (flag == 'g')
		g_sha256_g_buffer = value;
	else
		g_sha256_h_buffer = value;
	return (0);
}

int			sha256_add_to_buffer_variables(uint32_t value, int flag)
{
	if (flag == 'a')
		g_sha256_a_buffer += value;
	else if (flag == 'b')
		g_sha256_b_buffer += value;
	else if (flag == 'c')
		g_sha256_c_buffer += value;
	else if (flag == 'd')
		g_sha256_d_buffer += value;
	else if (flag == 'e')
		g_sha256_e_buffer += value;
	else if (flag == 'f')
		g_sha256_f_buffer += value;
	else if (flag == 'g')
		g_sha256_g_buffer += value;
	else
		g_sha256_h_buffer += value;
	return (0);
}

uint32_t	sha256_get_buffer_variables(int flag)
{
	if (flag == 'a')
		return (g_sha256_a_buffer);
	else if (flag == 'b')
		return (g_sha256_b_buffer);
	else if (flag == 'c')
		return (g_sha256_c_buffer);
	else if (flag == 'd')
		return (g_sha256_d_buffer);
	else if (flag == 'e')
		return (g_sha256_e_buffer);
	else if (flag == 'f')
		return (g_sha256_f_buffer);
	else if (flag == 'g')
		return (g_sha256_g_buffer);
	return (g_sha256_h_buffer);
}