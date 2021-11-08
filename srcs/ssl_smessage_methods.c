/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_smessage_methods.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 23:19:38 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/08 12:46:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char		**g_data;
static size_t	g_data_buffer_size;
static size_t	*g_data_size;
static size_t	g_bufindex;

void	ssl_init_data_buffer(void)
{
	g_data = (char **)ft_xmalloc(sizeof(char *) * (DATA_BUFFER + 1));
	g_data_size = (size_t *)ft_xmalloc(sizeof(size_t) * (DATA_BUFFER + 1));
	g_data_buffer_size = DATA_BUFFER;
	g_bufindex = 0;
}

/*
** In ft_realloc g_data_size is freed
*/

void	ssl_save_data(char *data, size_t data_size, t_ssl_messagetype type)
{
	void		*new_g_data_size;
	
	g_data[g_bufindex] = (char *)ft_xmalloc(sizeof(char *) * (data_size + 2));
	g_data[g_bufindex][0] = (char)type;
	ft_memcpy(g_data[g_bufindex] + 1, data, data_size);
	g_data_size[g_bufindex] = data_size;
	g_bufindex++;
	if (g_bufindex == g_data_buffer_size)
	{
		g_data = (char **)ft_memrealloc_array((void ***)&g_data, g_data_buffer_size,
				g_data_buffer_size * 2);
		new_g_data_size = ft_realloc((void *)g_data_size, g_data_buffer_size * sizeof(size_t),
				g_data_buffer_size * sizeof(size_t),
				g_data_buffer_size * sizeof(size_t) * 2);
		g_data_size = (size_t *)new_g_data_size;
		g_data_buffer_size *= 2;
	}
}

size_t	ssl_get_dataarray_index(size_t *data_buffer_size)
{
	*data_buffer_size = g_data_buffer_size;
	return (g_bufindex);
}

char	*ssl_get_data_algo(size_t *data_size, int flag_from_beginning)
{
	char		*current_data;
	
	if (flag_from_beginning)
		g_bufindex = 0;
	if (g_bufindex == g_data_buffer_size || !g_data_size[g_bufindex] ||
			!g_data[g_bufindex])
	{
		*data_size = 0;
		return (NULL);
	}
	*data_size = g_data_size[g_bufindex];
	if (g_data[g_bufindex][0] == FILE_DATA)
		current_data = interpret_file_data_algo(g_data[g_bufindex],
				data_size);
	else
		current_data = g_data[g_bufindex];
	g_bufindex++;
	return (current_data);
}

char	*ssl_get_data(size_t *data_size, int flag_from_beginning)
{
	char		*current_data;
	
	if (flag_from_beginning)
		g_bufindex = 0;
	if (g_bufindex == g_data_buffer_size || !g_data_size[g_bufindex] ||
			!g_data[g_bufindex])
	{
		*data_size = 0;
		return (NULL);
	}
	*data_size = g_data_size[g_bufindex];
	current_data = g_data[g_bufindex];
	g_bufindex++;
	return (current_data);
}

void	ssl_free_data_buffer(void)
{
	ft_arrdel(g_data);
	free(g_data_size);
	g_data = NULL;
	g_data_size = NULL;
}