/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_smessage_methods.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 23:19:38 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/24 00:56:54 by a18979859        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char		**g_data;
static size_t	g_data_buffer_size;
static size_t	*g_data_size;
static size_t	bufindex;

void	ssl_init_data_buffer(void)
{
	g_data = (char **)ft_xmalloc(sizeof(char *) * (DATA_BUFFER + 1));
	g_data_size = (size_t *)ft_xmalloc(sizeof(size_t) * (DATA_BUFFER + 1));
	g_data_buffer_size = DATA_BUFFER;
	bufindex = 0;
}

void	ssl_save_data(char *data, size_t data_size, t_ssl_messagetype type)
{
	g_data[bufindex] = (char *)ft_xmalloc(sizeof(char *) * (data_size + 2));
	g_data[bufindex][0] = (char)type;
	ft_memcpy(g_data[bufindex] + 1, data, data_size);
	free(data);
	g_data_size[bufindex] = data_size;
	bufindex++;
	if (bufindex == g_data_buffer_size)
	{
		g_data = ft_memrealloc_array(&g_data, g_data_buffer_size,
				g_data_buffer_size * 2);
		// g_data_size = ft_realloc(&g_data_size, g_data_buffer_size,
		// 		g_data_buffer_size * 2); //переделать на другую функцию.
		g_data_buffer_size *= 2;
	}
}

size_t	ssl_get_dataarray_index(size_t *data_buffer_size)
{
	*data_buffer_size = g_data_buffer_size;
	return (bufindex);
}

char	*ssl_get_data(size_t *data_size, int flag_from_beginning)
{
	if (flag_from_beginning)
		bufindex = 0;
	if (bufindex == g_data_buffer_size)
	{
		*data_size = 0;
		return (NULL);
	}
	*data_size = g_data_size[bufindex];
	return (g_data[bufindex] + 1);
}

void	ssl_free_data(void)
{
	ft_arrdel(g_data);
	free(g_data_size);
	g_data = NULL;
	g_data_size = NULL;
}