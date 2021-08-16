/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_hashcells_methods.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 21:53:04 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 19:11:18 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

/*
** Allocation of the new cell in the hashtable
*/

t_hashslot	*init_hashcell(void)
{
	t_hashslot	*hash_cell;

	hash_cell = (t_hashslot *)ft_xmalloc(sizeof(t_hashslot));
	return (hash_cell);
}

/*
** When cell is already allocated, it is filled
** only with the key and state.
** Data is not allocated from the one prepared by the user,
** in the table we just save a pointer.
*/

void	fill_hashcell(char *key, t_hashslot **hash_cell)
{
	(*hash_cell)->key = ft_strdup(key);
	(*hash_cell)->slot_state = SLOT_FILLED_HASH;
}

/*
** User can decide on the data he/she saves under each key
** in the hashtable. So the function to clean the data
** is taken from the one the user saves.
** Here we free all the cell content: data and key.
*/

void	delete_hashcell(int index,
			void **hashtable_array)
{
	t_hashslot	*hash_cell;
	void		(*clean_data_function)(void*);

	hash_cell = (t_hashslot *)hashtable_array[index];
	clean_data_function = get_clean_hashdata_function();
	if (hash_cell->data)
	{
		clean_data_function((void *)hash_cell->data);
		free(hash_cell->data);
		hash_cell->data = NULL;
	}
	if (hash_cell->key)
	{
		free(hash_cell->key);
		hash_cell->key = NULL;
	}
	hash_cell->slot_state = SLOT_DELETED_HASH;
}

void	print_hashcell(int index, void **hashtable_array,
			void (*print_data_function)(void *))
{
	t_hashslot	*slot_ptr;

	slot_ptr = (t_hashslot *)hashtable_array[index];
	if (slot_ptr->slot_state == SLOT_DELETED_HASH)
	{
		ft_printf("key and data are deleted\n");
		ft_printf("\n-------------------------------\n");
		return ;
	}
	ft_printf("slot key is %s\n", slot_ptr->key);
	ft_printf("slot data is:\n");
	print_data_function((void *)slot_ptr->data);
	ft_printf("\n-------------------------------\n");
}
