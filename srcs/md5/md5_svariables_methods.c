/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_svariables_methods.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 21:49:01 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/25 22:40:49 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static uint32_t	a_buffer;
static uint32_t	b_buffer;
static uint32_t	c_buffer;
static uint32_t	d_buffer;

int			init_buffer_variables(void)
{
	a_buffer = 0x67452301;
	b_buffer = 0xEFCDAB89;
	c_buffer = 0x98BADCFE;
	d_buffer = 0x10325476;
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