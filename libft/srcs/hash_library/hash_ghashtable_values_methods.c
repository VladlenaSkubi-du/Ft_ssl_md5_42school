/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_ghashtable_values_methods.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 21:52:40 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 19:11:05 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

/*
** The only way to change the hashtable value. Global variables
** can not be used by the user.
*/

size_t	get_hashtable_filled(void)
{
	return (g_hashtable_array_filled);
}

/*
** The only way to change the hashtable values. Global variables
** can not be used by the user.
** By each add of the new key hashtable_filled_value is changed
** with +1 and checked if the table is filled by 75%.
** By each delete of the key hashtable_filled_value is changed with
** -1 and checked if there are no programm errors.
** When the table is cleaned by the user or within the program,
** hashtable_filled_value becomes 0.
*/

size_t	change_hashtable_filled_value(int times)
{	
	if (times < 0)
	{
		if (change_hashtable_filled_decrement() == SIZET_MAX)
			return (SIZET_MAX);
	}
	else if (times > 0)
	{
		if (change_hashtable_filled_increment() == SIZET_MAX)
			return (SIZET_MAX);
	}
	else
		g_hashtable_array_filled = 0;
	return (0);
}

/*
** Check if g_hashtable_array_filled did not reach less than 0
** value (size_t will overflow)
*/

size_t	change_hashtable_filled_decrement(void)
{
	if (g_hashtable_array_filled - 1 > g_hashtable_array_filled)
		return (SIZET_MAX);
	g_hashtable_array_filled--;
	return (0);
}

/*
** If hashtable is filled on more than 75%, it is reallocated.
**
** For debugging:
** if (percent > 75 ||
** g_hashtable_array_filled / g_hashtable_array_size >= 1)
** printf("AFTER REALLOC:\n     g_hashtable_array_size = %zu\n     
** g_hashtable_array_filled = %zu\n",
** g_hashtable_array_size, g_hashtable_array_filled);
** 75% can be bad for hashtable sizes more than 30 cells length.
** Can be rewritten to some function that counts better
** percent according to the size of the table.
** But not now.
*/

size_t	change_hashtable_filled_increment(void)
{
	int			percent;

	g_hashtable_array_filled++;
	percent = hashtable_count_filled_percent(g_hashtable_array_filled,
			g_hashtable_array_size);
	if (percent > 75
		|| g_hashtable_array_filled / g_hashtable_array_size >= 1)
	{
		if (hashtable_realloc() == SIZET_MAX)
			return (SIZET_MAX);
	}
	return (0);
}

/*
** Counting the percentage of how filled is hashtable.
** Should be always less than 100% to have at least one
** cell left for new addition.
**
** For debugging:
** printf("-> difference: %d\n", result);
*/

int	hashtable_count_filled_percent(size_t filled,
		size_t size)
{
	int			result;

	result = (int)(filled / (size + 0.0) * 100);
	return (result);
}
