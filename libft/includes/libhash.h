/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libhash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:17:18 by a18979859         #+#    #+#             */
/*   Updated: 2021/08/16 19:24:52 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBHASH_H
# define LIBHASH_H

# include "libft.h"

/*
** ____________________________________________________________________________
*/

/*
** @HASHTABLE_LENGTH is how many hashtable cells we allocate in the beginning
** @KEY_LENGTH is the length of the key created by the user.
*/

# define HASHTABLE_LENGTH	11
# define KEY_LENGTH			256

/*
** ____________________________________________________________________________
*/

/*
** Each hashtable cell can be empty - it will be just NULL;
** deleted - it will be allocated, key will be NULL, data NULL, state
** @SLOT_DELETED_HASH;
** filled - it will be allocated, key allocated and saved, data
** allocated and saved, state @SLOT_FILLED_HASH.
*/

typedef enum s_hashslotstate
{
	SLOT_DELETED_HASH,
	SLOT_FILLED_HASH,
}						t_hashslotstate;

/*
** All the errors possible can be programm errors if
** something was not allocated or the hashtable is too long.
** Other user errors are described.
** @ADD_CELLEXISTS = ft_printf("Such cell already exists.
** You can find its index with the use of -f option\n");
** @DELETE_HASHTABLE_EMPTY = ft_printf("Hashtable is empty\n");
** @FIND_NOKEY = ft_printf("There is no such key in the hashtable\n");
*/

typedef enum s_hasherrors
{
	PROGRAMM_ERROR = 0,
	ADD_CELLEXISTS,
	DELETE_HASHTABLE_EMPTY,
	FIND_NOKEY,
}						t_hasherrors;

/*
** @key is a cell id, generated by the user, can not be
** longer than KEY_LENGTH
** @data is a data structure saved in the cell, attributes by id
** @slot_state is a data state, see the description of the
** structure.
*/

typedef struct s_hashslot
{
	char				*key;
	void				*data;
	t_hashslotstate		slot_state;
}						t_hashslot;

/*
** ____________________________________________________________________________
*/

/*
** @g_hashtable_array is a hashtable itself
** @g_hashtable_array_size is a hashtable size
** @g_hashtable_array_filled increases each time the user adds a key,
** decreases each time he deletes a key/keys
** This variables can be changes only by methods in 2 files:
** hash_ghashtable_*.c. Can not be changed by the user directly.
*/

void					**g_hashtable_array;
size_t					g_hashtable_array_size;
size_t					g_hashtable_array_filled;

/*
** ____________________________________________________________________________
*/

/*
** File hash_ghashtable_methods.c
*/

int						hashtable_init(void);
int						hashtable_remove(void);
void					**get_hashtable_value(size_t *size);
size_t					hashtable_realloc(void);
size_t					hashtable_realloc_insert_hash(
							void ***new_hashtable_array,
							size_t new_hashtable_array_size,
							size_t *new_hashtable_array_filled,
							size_t index_in_old);

/*
** File hash_hashtable_methods.c
*/

void					hashtable_clean(void **hashtable_array,
							size_t hashtable_array_size);

/*
** File hash_ghashtable_values_methods.c
*/

size_t					get_hashtable_filled(void);
size_t					change_hashtable_filled_value(int times);
size_t					change_hashtable_filled_decrement(void);
size_t					change_hashtable_filled_increment(void);
int						hashtable_count_filled_percent(size_t filled,
							size_t size);				

/*
** File hash_shashdata_values_methods.c
*/

void					save_clean_hashdata_function(
							void (*clean_data_function)(void*));
void					*get_clean_hashdata_function(void);

/*
** File hash_hashcells_methods.c
*/

t_hashslot				*init_hashcell(void);
void					fill_hashcell(char *key,
							t_hashslot **hash_cell);
void					delete_hashcell(int index,
							void **hashtable);
void					print_hashcell(int index, void **hashtable,
							void (*print_data_function)(void*));

/*
** File hash_hashindex_find.c
*/

size_t					hashtable_find_index_ifempty(void **hashtable,
							size_t hashtable_size, char *key);
size_t					hashtable_find_index_ifdeleted(void **hashtable,
							size_t hashtable_size, char *key, size_t index);
size_t					hashtable_find_index_iffilled(void **hashtable,
							size_t hashtable_size, char *key);

/*
** File hash_hashfunction.c
*/

size_t					hashfunction(char *key,
							size_t hashtable_size, size_t times);
size_t					hashfunction_main(const char *key,
							size_t key_length);
size_t					hashfunction_double_hash(const char *key,
							size_t key_length);

#endif