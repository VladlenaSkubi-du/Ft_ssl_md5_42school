/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_smessage_methods.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 23:19:38 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/14 23:25:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char		*g_data;
static size_t	g_data_size;

void	ssl_save_data(char *data, size_t data_size)
{
	g_data = data;
	g_data_size = data_size;
}

char	*ssl_get_data(size_t *data_size)
{
	*data_size = g_data_size;
	return (g_data);
}

void	ssl_free_data(void)
{
	free(g_data);
	g_data = NULL;
	g_data_size = 0;
}