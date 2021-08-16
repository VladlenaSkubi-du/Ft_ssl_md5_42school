/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_ghashtable_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:44:09 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 19:12:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

/*
** Is used by the user in the beginning of work with hashtable
*/

int	hashtable_init(void)
{
	g_hashtable_array_size = HASHTABLE_LENGTH;
	g_hashtable_array = (void **)ft_xmalloc(sizeof(void *)
			* (g_hashtable_array_size + 1));
	g_hashtable_array_filled = 0;
	return (0);
}

/*
** Is used by the user in the end of work with hashtable
** or within hash programm
*/

int	hashtable_remove(void)
{	
	hashtable_clean(g_hashtable_array, g_hashtable_array_size);
	g_hashtable_array_filled = 0;
	g_hashtable_array_size = 0;
	free(g_hashtable_array);
	g_hashtable_array = NULL;
	return (0);
}

/*
** The only way to get and use the hashtable. Global variables
** can not be used by the user.
*/

void	**get_hashtable_value(size_t *size)
{
	*size = g_hashtable_array_size;
	return (g_hashtable_array);
}

/*
** The only way to change the hashtable. Global variables
** can not be used by the user.
** The table is realloced when it is filled by 75%.
*/

size_t	hashtable_realloc(void)
{
	void		**new_hashtable_array;
	size_t		new_hasht_array_size;
	size_t		new_hashtable_array_filled;
	size_t		i;

	new_hasht_array_size = ft_find_next_prime_num(g_hashtable_array_size * 2);
	new_hashtable_array = (void **)ft_xmalloc(sizeof(void *)
			* (new_hasht_array_size + 1));
	new_hashtable_array_filled = 0;
	i = 0;
	while (i < g_hashtable_array_size)
	{
		if (g_hashtable_array[i])
		{
			hashtable_realloc_insert_hash(&new_hashtable_array,
				new_hasht_array_size,
				&new_hashtable_array_filled, i);
		}
		i++;
	}
	hashtable_remove();
	g_hashtable_array = new_hashtable_array;
	g_hashtable_array_size = new_hasht_array_size;
	g_hashtable_array_filled = new_hashtable_array_filled;
	return (0);
}

/*
** We can not just allocate a new array and copy from the old one.
** We need to count in which index of the new array each key and
** its data should lie.
*/

size_t	hashtable_realloc_insert_hash(void ***new_hashtable_array,
			size_t new_hashtable_array_size,
			size_t *new_hashtable_array_filled,
			size_t index_in_old)
{
	t_hashslot	*slot_ptr;
	size_t		index_in_new;

	slot_ptr = (t_hashslot *)g_hashtable_array[index_in_old];
	if (slot_ptr->slot_state == SLOT_FILLED_HASH)
	{
		index_in_new = hashtable_find_index_ifempty(*new_hashtable_array,
				new_hashtable_array_size, slot_ptr->key);
		if (index_in_new == SIZET_MAX)
			return (SIZET_MAX);
		(*new_hashtable_array)[index_in_new] = g_hashtable_array[index_in_old];
		(*new_hashtable_array_filled)++;
		g_hashtable_array[index_in_old] = NULL;
	}
	return (0);
}
