/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_cmd_hashmethods.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 10:41:37 by a18979859         #+#    #+#             */
/*   Updated: 2021/08/23 10:43:26 by a18979859        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_cmd_list.h"

size_t	ssl_save_commands_hashlist(void)
{
	void			**hashtable;
	size_t			hashtable_size;
	size_t			hashtable_filled;
	size_t			i;

	hashtable_size = SIZET_MAX;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size == SIZET_MAX)
		return (SIZET_MAX);
	hashtable_filled = get_hashtable_filled();
	if (hashtable_filled == 0)
		return (DELETE_HASHTABLE_EMPTY);
	i = 0;
	while (i < hashtable_size)
	{
		if (hashtable[i])
			print_hashcell(i, hashtable,
				&print_hashdata);
		i++;
	}
	return (0);
}

size_t	ssl_save_commands_hashadd(char *key)
{
	size_t		index;
	void		**hashtable;
	size_t		hashtable_size;
	size_t		hashtable_filled;
	t_hashslot	*slot_ptr;
	
	hashtable_size = SIZET_MAX;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size == SIZET_MAX)
		return (SIZET_MAX);
	hashtable_filled = get_hashtable_filled();
	index = hashtable_find_index_ifempty(hashtable, hashtable_size, key);
	if (index == SIZET_MAX)
		return (SIZET_MAX);
	slot_ptr = (t_hashslot *)hashtable[index];
	if (slot_ptr && slot_ptr->slot_state == SLOT_FILLED_HASH)
		return (ADD_CELLEXISTS);
	if (!slot_ptr)
		slot_ptr = init_hashcell();
	fill_hashcell(key, &slot_ptr);
	slot_ptr->data = NULL;
	hashtable[index] = (void *)slot_ptr;
	if (change_hashtable_filled_value(1) == SIZET_MAX)
		return (SIZET_MAX);
	return (0);
}

size_t	ssl_save_commands_hashfind(char *key)
{
	void			**hashtable;
	size_t			hashtable_size;
	size_t			hashtable_filled;
	size_t			index;

	hashtable_size = SIZET_MAX;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size == SIZET_MAX)
		return (SIZET_MAX);
	hashtable_filled = get_hashtable_filled();
	if (hashtable_filled == 0)
		return (SIZET_MAX);
	index = hashtable_find_index_iffilled(hashtable, hashtable_size, key);
	if (index == SIZET_MAX)
		return (SIZET_MAX);
	return (index);
}

/*
** User can decide on the data he/she saves under each key
** in the hashtable. There should be exactly 5 functions in order to
** work with data structures within libhash.
** Here data consists of a string and an integer.
*/

void	clean_hashdata(void *cell_data)
{
	if (cell_data == NULL)
		return ;
}

void	print_hashdata(void *cell_data)
{
	if (cell_data == NULL)
		ft_putendl_fd("No hashdata", STDOUT_FILENO);
}
