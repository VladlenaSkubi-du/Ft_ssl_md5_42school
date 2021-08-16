/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_hashfunction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:09:41 by a18979859         #+#    #+#             */
/*   Updated: 2021/08/09 21:55:14 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

/*
** In this function we count the hashtable index according to the key
** by using a hashfunction. If the attempt to find the index is the first
** we use main function. For all the other attempts we use another function
** based on the method of double_hash.
**
** For debugging:
** if (attempt == 0)
** printf("    first index mod hashtablesize = %zu\n",
** final_index % hashtable_size);
** 
** printf("    next final_index mod hashtablesize = %zu\n",
** final_index % hashtable_size);
** return (final_index % hashtable_size); (in the end)
*/

size_t	hashfunction(char *key, size_t hashtable_size, size_t attempt)
{
	size_t		final_index;

	final_index = hashfunction_main(key, ft_strlen(key));
	if (attempt == 0)
		return (final_index % hashtable_size);
	final_index = final_index + attempt
		* hashfunction_double_hash(key, ft_strlen(key));
	return (final_index % hashtable_size);
}

/*
** Here we use function named JS Hash Function written by Justin Sobel
** Link: http://www.partow.net/programming/hashfunctions/#HashAndPrimes
**
** For debugging:
** return (key_length);
*/

size_t	hashfunction_double_hash(const char *key, size_t key_length)
{
	size_t		hash;
	size_t		i;

	hash = 1315423911;
	i = 0;
	while (i < key_length)
	{
		hash ^= ((hash << 5) + (*key) + (hash >> 2));
		++key;
		++i;
	}
	return (hash);
}

/*
** Here we use function named DJB Hash Function written by Professor Daniel J
** Link: http://www.partow.net/programming/hashfunctions/#HashAndPrimes
**
** For debugging:
** return (key_length);
*/

size_t	hashfunction_main(const char *key, size_t key_length)
{
	size_t		hash;
	size_t		i;

	hash = 5381;
	i = 0;
	while (i < key_length)
	{
		hash = ((hash << 5) + hash) + (*key);
		++key;
		++i;
	}
	return (hash);
}
