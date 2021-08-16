/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_hashindex_find.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:01:21 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 19:13:52 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

static size_t	new_norm_ternary_times(size_t hashtable_size,
					size_t attempt)
{
	if (hashtable_size - attempt < hashtable_size)
		return (ft_find_factorial(hashtable_size - attempt));
	return (0);
}

/*
** In this function we try to find the empty cell.
** Each time we do not find the empty one
** the number of attempts increases and the number of
** variants left becomes factorial of hashtable_size minus number of
** the attempt.
** For example, if hashtable size is 5, there is a wrong or no key
** in the cell found after the first attempt, number of tries
** will be reduced to !(5 - 1) or 24.
** There are two possible valid returns from the function -
** 1) cell does not exist so it is empty,
** 2) such key is already filled to some cell.
** If on our way to the empty cell we find deleted ones, before filling in
** the cell, we check if such key is already somewhere with the help of
** hashtable_find_index_ifdeleted function.
** Overwise, if there are errors in hashfunction,
** the function will return an error.
**
** For debugging:
** if (slot_ptr && slot_ptr->slot_state == SLOT_FILLED_HASH &&
**				ft_strcmp(slot_ptr->key, key) == 0)
** printf("    the same key\n");
** if (!hashtable[index])
** printf("    empty slot\n");
*/

size_t	hashtable_find_index_ifempty(void **hashtable,
			size_t hashtable_size, char *key)
{
	t_hashslot		*slot_ptr;
	size_t			index;
	size_t			times;
	size_t			attempt;

	times = hashtable_size;
	attempt = 0;
	while (times)
	{
		index = hashfunction(key, hashtable_size, attempt);
		if (index == SIZET_MAX)
			return (SIZET_MAX);
		if (!hashtable[index])
			return (index);
		slot_ptr = (t_hashslot *)hashtable[index];
		if (slot_ptr && slot_ptr->slot_state == SLOT_DELETED_HASH)
			return (hashtable_find_index_ifdeleted(hashtable,
					hashtable_size, key, index));
		if (slot_ptr && slot_ptr->slot_state == SLOT_FILLED_HASH
			&& ft_strcmp(slot_ptr->key, key) == 0)
			return (index);
		attempt++;
		times = new_norm_ternary_times(hashtable_size, attempt);
	}
	return (SIZET_MAX);
}

/*
** In this function we try to find the filled cell
** according to the key. If we can not find it, it means
** that such key was not added to the table before.
** So we return the index of the cell with the state
** "Deleted". If we find such key, it means that it was
** already added to the table so we return its index.
**
** For debugging:
** printf("    the same key\n");
** return (index_new); (in the end)
*/

size_t	hashtable_find_index_ifdeleted(void **hashtable,
			size_t hashtable_size, char *key, size_t index)
{
	size_t			index_new;

	index_new = hashtable_find_index_iffilled(hashtable, hashtable_size, key);
	if (index_new == SIZET_MAX)
		return (index);
	return (index_new);
}

/*
** In this function we try to find the filled cell
** according to the key. Each time we do not find the cell
** the number of attempts increases and the number of
** variants left becomes factorial of hashtable_size minus number of
** the attempt.
** For example, if hashtable size is 5, there is a wrong or no key
** in the cell found after the first attempt, number of tries
** will be reduced to !(5 - 1) or 24.
** There is one possible valid return from the function -
** cell exists, its status is filled and the key is right.
** Overwise, if there are errors in hashfunction or there is
** no key (the cell we are looking for can be deleted),
** the function will return an error.
**
** For debugging:
** Within if (hashtable[index]):
** if (slot_ptr && slot_ptr->slot_state == SLOT_DELETED_HASH)
** printf("    already deleted\n");
*/

size_t	hashtable_find_index_iffilled(void **hashtable,
			size_t hashtable_size, char *key)
{
	t_hashslot		*slot_ptr;
	size_t			index;
	size_t			times;
	size_t			attempt;
	int				res;

	times = hashtable_size;
	attempt = 0;
	while (times)
	{
		index = hashfunction(key, hashtable_size, attempt);
		if (index == SIZET_MAX)
			return (SIZET_MAX);
		if (hashtable[index])
		{
			slot_ptr = (t_hashslot *)hashtable[index];
			res = ft_strcmp(slot_ptr->key, key);
			if (slot_ptr && slot_ptr->slot_state == SLOT_FILLED_HASH
				&& res == 0)
				return (index);
		}
		attempt++;
		times = new_norm_ternary_times(hashtable_size, attempt);
	}
	return (SIZET_MAX);
}
