/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_hashdata_methods.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:11:56 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/11 14:52:11 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_cmd_list.h"

/*
** User can decide on the data he/she saves under each key
** in the hashtable. There should be exactly 5 functions in order to
** work with data structures within libhash.
** Here data consists of a string and an integer.
*/

void			*init_hashdata(void)
{
	t_celldata	*cmd_attributes;

	cmd_attributes = (t_celldata *)ft_xmalloc(sizeof(t_celldata));
	return ((void *)cmd_attributes);
}

void			fill_hashdata(void **cell_data, char *options,
					int (*start_algo_function)(size_t))
{
	t_celldata	*cmd_attributes;

	cmd_attributes = (t_celldata *)(*cell_data);
	cmd_attributes->flags = ft_strdup(options);
	cmd_attributes->start_algo_function = start_algo_function;
}

void			copy_hashdata(void **cell_data, void *data)
{
	t_celldata	*cmd_attributes_old;
	t_celldata	*cmd_attributes_new;

	cmd_attributes_old = (t_celldata *)data;
	cmd_attributes_new = (t_celldata *)(*cell_data);
	cmd_attributes_new->flags = ft_strdup(cmd_attributes_old->flags);
	cmd_attributes_new->start_algo_function =
		cmd_attributes_old->start_algo_function;
	*cell_data = cmd_attributes_new;
}

void			clean_hashdata(void *cell_data)
{
	t_celldata	*cmd_attributes;

	cmd_attributes = (t_celldata *)cell_data;
	free(cmd_attributes->flags);
	cmd_attributes->flags = NULL;
	cmd_attributes->start_algo_function = NULL;
}

void			print_hashdata(void *cell_data)
{
	t_celldata	*cmd_attributes;

	cmd_attributes = (t_celldata *)cell_data;
	ft_printf("  data -> command flags are %s\n", cmd_attributes->flags);
	ft_printf("  data -> command function address is %p\n",
		cmd_attributes->start_algo_function);
}
