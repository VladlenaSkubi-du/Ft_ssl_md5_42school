/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sbytesorder_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 15:44:00 by sschmele          #+#    #+#             */
/*   Updated: 2021/09/30 22:42:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	g_bytes_order;

/*
** Here we are looking on the left byte of the uint32_t number check
** If it is 1 then processor's bytes order is little endian
*/

int			save_bytes_order(void)
{
	uint32_t	check;
    uint8_t		*p;
	
	check = 1;
	p = (uint8_t *)(check);
    if (*p == 1)
        g_bytes_order = LITTLE_ENDIAN;
    else
        g_bytes_order = BIG_ENDIAN;
	return (0);
}

int         get_bytes_order(void)
{
    return (g_bytes_order);
}