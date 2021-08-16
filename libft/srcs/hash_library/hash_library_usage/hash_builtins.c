/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:08:50 by a18979859         #+#    #+#             */
/*   Updated: 2021/08/09 21:46:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash_usage.h"

/*
** All this functions are basic if you need a hash library to
** work as a builtin in bash. If not, make your own functions
** taking this ones into account.
*/

size_t	btin_hash_list_hashtable(void)
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

size_t	btin_hash_valid_argument_add(char *key, void *data)
{
	size_t			index;
	void			**hashtable;
	size_t			hashtable_size;
	size_t			hashtable_filled;
	t_hashslot		*slot_ptr;

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
	slot_ptr->data = data;
	hashtable[index] = (void *)slot_ptr;
	if (change_hashtable_filled_value(1) == SIZET_MAX)
		return (SIZET_MAX);
	return (0);
}

/*
** For debugging:
** slot_ptr = (t_hashslot*)hashtable[index];
** if (slot_ptr && slot_ptr->slot_state == SLOT_DELETED_HASH)
** return (0);
** delete_hashcell(index, hashtable);
*/

size_t	btin_hash_valid_argument_delete(char *key)
{
	size_t			index;
	void			**hashtable;
	size_t			hashtable_size;
	size_t			hashtable_filled;
	t_hashslot		*slot_ptr;

	hashtable_size = SIZET_MAX;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size == SIZET_MAX)
		return (SIZET_MAX);
	hashtable_filled = get_hashtable_filled();
	if (hashtable_filled == 0)
		return (DELETE_HASHTABLE_EMPTY);
	index = hashtable_find_index_iffilled(hashtable, hashtable_size, key);
	if (index == SIZET_MAX)
		return (FIND_NOKEY);
	slot_ptr = (t_hashslot *)hashtable[index];
	delete_hashcell(index, hashtable);
	if (change_hashtable_filled_value(-1) == SIZET_MAX)
		return (SIZET_MAX);
	hashtable_filled = get_hashtable_filled();
	if (hashtable_filled == 0)
		hashtable_clean(hashtable, hashtable_size);
	return (0);
}

size_t	btin_hash_clean_hashtable(void)
{
	void			**hashtable;
	size_t			hashtable_size;
	size_t			hashtable_filled;

	hashtable_size = SIZET_MAX;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size == SIZET_MAX)
		return (SIZET_MAX);
	hashtable_filled = get_hashtable_filled();
	if (hashtable_filled == 0)
		return (DELETE_HASHTABLE_EMPTY);
	hashtable_clean(hashtable, hashtable_size);
	change_hashtable_filled_value(0);
	return (0);
}

size_t	btin_hash_valid_argument_find(char *key)
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
		return (DELETE_HASHTABLE_EMPTY);
	index = hashtable_find_index_iffilled(hashtable, hashtable_size, key);
	if (index == SIZET_MAX)
		return (FIND_NOKEY);
	ft_printf("Key %s is in the cell with index %zu\n", key, index);
	return (index);
}
