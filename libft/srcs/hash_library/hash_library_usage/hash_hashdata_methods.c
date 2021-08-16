/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_hashdata_methods.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:09:35 by a18979859         #+#    #+#             */
/*   Updated: 2021/08/16 19:18:20 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash_usage.h"

/*
** User can decide on the data he/she saves under each key
** in the hashtable. There should be exactly 5 functions in order to
** work with data structures within libhash.
** Here data consists of a string and an integer.
*/

void	*init_hashdata(void)
{
	t_celldata	*cmd_attributes;

	cmd_attributes = (t_celldata *)ft_xmalloc(sizeof(t_celldata));
	return ((void *)cmd_attributes);
}

void	fill_hashdata(void **cell_data, char *path, int number)
{
	t_celldata	*cmd_attributes;

	cmd_attributes = (t_celldata *)(*cell_data);
	cmd_attributes->path = ft_strdup(path);
	cmd_attributes->number = number;
}

void	copy_hashdata(void **cell_data, void *data)
{
	t_celldata	*cmd_attributes_old;
	t_celldata	*cmd_attributes_new;

	cmd_attributes_old = (t_celldata *)data;
	cmd_attributes_new = (t_celldata *)(*cell_data);
	cmd_attributes_new->path = ft_strdup(cmd_attributes_old->path);
	cmd_attributes_new->number = cmd_attributes_old->number;
	*cell_data = cmd_attributes_new;
}

void	clean_hashdata(void *cell_data)
{
	t_celldata	*cmd_attributes;

	cmd_attributes = (t_celldata *)cell_data;
	free(cmd_attributes->path);
	cmd_attributes->path = NULL;
	cmd_attributes->number = 0;
}

void	print_hashdata(void *cell_data)
{
	t_celldata	*cmd_attributes;

	cmd_attributes = (t_celldata *)cell_data;
	ft_printf("  data -> command path is %s\n", cmd_attributes->path);
	ft_printf("  data -> command was called %d times\n", cmd_attributes->number);
}
