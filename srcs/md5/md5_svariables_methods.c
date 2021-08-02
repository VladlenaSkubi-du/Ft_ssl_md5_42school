/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_svariables_methods.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 21:49:01 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/02 15:48:42 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static uint32_t	a0;
static uint32_t	b0;
static uint32_t	c0;
static uint32_t	d0;

static uint32_t	a_buffer;
static uint32_t	b_buffer;
static uint32_t	c_buffer;
static uint32_t	d_buffer;

int			init_buffer0_variables(void) // add another const for big-endian
{
	a0 = 0x67452301;
	b0 = 0xEFCDAB89;
	c0 = 0x98BADCFE;
	d0 = 0x10325476;
	return (0);
}

int			init_buffer_variables(void)
{
	a_buffer = a0;
	b_buffer = b0;
	c_buffer = c0;
	d_buffer = d0;
	return (0);
}

int			save_buffer_variables(uint32_t value, int flag)
{
	if (flag == 'a')
		a_buffer = value;
	else if (flag == 'b')
		b_buffer = value;
	else if (flag == 'c')
		c_buffer = value;
	else
		d_buffer = value;
	return (0);
}

int			add_to_buffer_variables(uint32_t value, int flag)
{
	if (flag == 'a')
		a_buffer += value;
	else if (flag == 'b')
		b_buffer += value;
	else if (flag == 'c')
		c_buffer += value;
	else
		d_buffer += value;
	return (0);
}

int			get_buffer_variables(int flag)
{
	if (flag == 'a')
		return (a_buffer);
	else if (flag == 'b')
		return (b_buffer);
	else if (flag == 'c')
		return (c_buffer);
	return (d_buffer);
}