/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_cmd_hashmethods.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 10:41:37 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/07 16:20:04 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_cmd_list.h"

size_t			ssl_save_commands_hashlist(void)
{
	void		**hashtable;
	size_t		hashtable_size;
	size_t		hashtable_filled;
	size_t		i;

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

size_t			ssl_save_commands_hashadd(char *key, void *data)
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
	slot_ptr->data = data;
	hashtable[index] = (void *)slot_ptr;
	if (change_hashtable_filled_value(1) == SIZET_MAX)
		return (SIZET_MAX);
	return (0);
}

size_t			ssl_save_commands_hashfind(char *key)
{
	void		**hashtable;
	size_t		hashtable_size;
	size_t		hashtable_filled;
	size_t		index;

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

t_celldata		*ssl_get_data_from_hashtable(size_t answer_cmd)
{
	void		**hashtable;
	size_t		hashtable_size;
	t_hashslot	*slot_ptr;
	t_celldata	*cmd_data;

	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size == SIZET_MAX)
	{
		ssl_errors_management(ERR_PROGRAMM, NULL, 0, 0);
		return (NULL);
	}
	slot_ptr = (t_hashslot *)hashtable[answer_cmd];
	cmd_data = slot_ptr->data;
	return (cmd_data);
}
