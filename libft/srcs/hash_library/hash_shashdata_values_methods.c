/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_shashdata_values_methods.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:27:03 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 19:16:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

static void	(*g_clean_data_function)(void *cell_data);

/*
** User can decide on the data he/she saves under each key
** in the hashtable. So the function to clean the data
** is taken from the one the user saves.
** Here we give the libhash instruments to work with the functions.
*/

void	save_clean_hashdata_function(void (*clean_data_function)(void *))
{
	g_clean_data_function = clean_data_function;
}

void	*get_clean_hashdata_function(void)
{
	return (g_clean_data_function);
}
