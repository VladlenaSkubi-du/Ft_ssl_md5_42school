/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_soutput_buffer_methods.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 12:29:31 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/17 14:48:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char     **g_output_results;
static size_t	g_bufindex;

void			ssl_init_output_buffer(void)
{
	size_t		output_results_buffer;
	
	ssl_get_dataarray_index(&output_results_buffer);
	g_output_results = (char **)ft_xmalloc(sizeof(char *)
		* (output_results_buffer + 1));
	g_bufindex = 0;
}

void			ssl_save_output(char *output_hash)
{
	size_t		output_results_buffer;
	
	ssl_get_dataarray_index(&output_results_buffer);
	if (g_bufindex == output_results_buffer)
		return ;
	g_output_results[g_bufindex] = output_hash;
	g_bufindex++;
}

char			*ssl_get_output(int flag_from_beginning)
{
	size_t		output_results_buffer;
	char		*hash_line;
	
	ssl_get_dataarray_index(&output_results_buffer);
	if (flag_from_beginning)
		g_bufindex = 0;
	if (g_bufindex == output_results_buffer || !g_output_results[g_bufindex])
		return (NULL);
	hash_line = g_output_results[g_bufindex];
	g_bufindex++;
	return (hash_line);
}

void			ssl_free_output_buffer(void)
{
	ft_arrdel(g_output_results);
	g_output_results = NULL;
}
