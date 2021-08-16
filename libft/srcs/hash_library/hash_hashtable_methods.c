/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_hashtable_methods.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:30:23 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/09 22:05:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

/*
** Is used within the program in order to free the hashtable by
** users command or when reallocation of the hashtable happens.
*/

void	hashtable_clean(void **hashtable_array,
			size_t hashtable_array_size)
{
	size_t		i;

	i = 0;
	while (i < hashtable_array_size)
	{
		if (hashtable_array[i])
		{
			delete_hashcell(i, hashtable_array);
			free(hashtable_array[i]);
			hashtable_array[i] = NULL;
		}
		i++;
	}
}
