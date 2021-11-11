/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_prepare_output_results.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 12:29:31 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/11 15:31:08 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char     **g_output_results;
static size_t	bufindex;

void			ssl_init_output_buffer(void)
{
	size_t		output_results_buffer;
	
	ssl_get_dataarray_index(&output_results_buffer);
	g_output_results = (char **)ft_xmalloc(sizeof(char *)
		* (output_results_buffer + 1));
	bufindex = 0;
}

void			ssl_save_output(char *output_hash)
{
	g_output_results[bufindex] = output_hash;
	bufindex++;
}

char			*ssl_get_output(int flag_from_beginning)
{
	size_t		output_results_buffer;
	char		*hash_line;
	
	ssl_get_dataarray_index(&output_results_buffer);
	if (flag_from_beginning)
		bufindex = 0;
	if (bufindex == output_results_buffer || !g_output_results[bufindex])
		return (NULL);
	hash_line = g_output_results[bufindex];
	bufindex++;
	return (hash_line);
}

void			ssl_free_output_buffer(void)
{
	ft_arrdel(g_output_results);
	g_output_results = NULL;
}
