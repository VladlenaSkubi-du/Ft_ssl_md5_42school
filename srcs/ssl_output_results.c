/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_output_results.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 12:29:31 by a18979859         #+#    #+#             */
/*   Updated: 2021/10/11 11:54:21 by a18979859        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char     **g_output_results;
static size_t	bufindex;

void	ssl_init_output_buffer(void)
{
	size_t	output_results_buffer;
	
	ssl_get_dataarray_index(&output_results_buffer);
	g_output_results = (char **)ft_xmalloc(sizeof(char *)
		* (output_results_buffer + 1));
	bufindex = 0;
}

void	ssl_save_output(char *output_hash)
{
	g_output_results[bufindex] = output_hash;
	bufindex++;
}

char	*ssl_get_output(int flag_from_beginning)
{
	size_t	output_results_buffer;
	
	ssl_get_dataarray_index(&output_results_buffer);
	if (flag_from_beginning)
		bufindex = 0;
	if (bufindex == output_results_buffer)
		return (NULL);
	return (g_output_results[bufindex]);
}

void	ssl_free_output_buffer(void)
{
	ft_arrdel(g_output_results);
	g_output_results = NULL;
}

static char	*ssl_data_find_filename(char *data_message)
{
	char	*filename;
	char	filename_size;
	int		answer;
	size_t	i;

	filename_size = data_message[1];
	i = 1;
	while (data_message[i])
	{
		if (data_message[i] == filename_size)
		{
			answer = ft_strncmp(data_message + i + 1,
					STOP_FILENAME_SEQ, 5);
			if (answer == 0)
				break ;
		}
		i++;
	}
	filename = ft_strndup(data_message + 2, filename_size);
	return (filename);
}

int		ssl_output_results(int flags)
{
	char	*data_message;
	char	*filename;
	size_t	needed;
	size_t	i;

	needed = 0;
	data_message = ssl_get_data(&needed, 0);
	while (1)
	{
		if (data_message[0] == FILE_DATA)
			filename = ssl_data_find_filename(data_message);
	}
	free(filename);
	return (0);
}