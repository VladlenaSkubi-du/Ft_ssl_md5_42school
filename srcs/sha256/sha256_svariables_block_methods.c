/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_svariables_block_methods.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:42:54 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/16 20:28:04 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

static uint32_t	g_sha256_a_before_block;
static uint32_t	g_sha256_b_before_block;
static uint32_t	g_sha256_c_before_block;
static uint32_t	g_sha256_d_before_block;
static uint32_t	g_sha256_e_before_block;
static uint32_t	g_sha256_f_before_block;
static uint32_t	g_sha256_g_before_block;
static uint32_t	g_sha256_h_before_block;

int			sha256_save_buffer_before_block(void)
{
	uint32_t	aa;
	uint32_t	bb;
	uint32_t	cc;
	uint32_t	dd;
	uint32_t	ee;
	uint32_t	ff;
	uint32_t	gg;
	uint32_t	hh;
	
	aa = sha256_get_buffer_variables('a');
	bb = sha256_get_buffer_variables('b');
	cc = sha256_get_buffer_variables('c');
	dd = sha256_get_buffer_variables('d');
	ee = sha256_get_buffer_variables('e');
	ff = sha256_get_buffer_variables('f');
	gg = sha256_get_buffer_variables('g');
	hh = sha256_get_buffer_variables('h');
	g_sha256_a_before_block = aa;
	g_sha256_b_before_block = bb;
	g_sha256_c_before_block = cc;
	g_sha256_d_before_block = dd;
	g_sha256_e_before_block = ee;
	g_sha256_f_before_block = ff;
	g_sha256_g_before_block = gg;
	g_sha256_h_before_block = hh;
	return (0);
}

int			sha256_save_buffer_after_block(void)
{
	sha256_add_to_buffer_variables(g_sha256_a_before_block, 'a');
	sha256_add_to_buffer_variables(g_sha256_b_before_block, 'b');
	sha256_add_to_buffer_variables(g_sha256_c_before_block, 'c');
	sha256_add_to_buffer_variables(g_sha256_d_before_block, 'd');
	sha256_add_to_buffer_variables(g_sha256_e_before_block, 'e');
	sha256_add_to_buffer_variables(g_sha256_f_before_block, 'f');
	sha256_add_to_buffer_variables(g_sha256_g_before_block, 'g');
	sha256_add_to_buffer_variables(g_sha256_h_before_block, 'h');
	return (0);
}