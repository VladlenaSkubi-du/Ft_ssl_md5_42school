/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libhash_usage.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:10:20 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 19:21:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBHASH_USAGE_H
# define LIBHASH_USAGE_H

# include <stdio.h>
# include "libhash.h"
# include "libft.h"

# define PROGRAM_NAME			"./ehash"
# define PROGRAM_FLAGS_ARG		"df"
# define PROGRAM_FLAGS_NO_ARG	"lrh"
# define FLAG_L					0x1
# define FLAG_D					0x2
# define FLAG_R					0x4
# define FLAG_F					0x8
# define FLAG_H					0x10

/*
** What the data of each cell in the hashtable
** should consist of
*/

typedef struct s_celldata
{
	char				*path;
	int					number;
}						t_celldata;

typedef enum s_hash_usererrors
{
	KEY_TOO_LONG = 4,
}						t_hash_usererrors;

/*
** File hash_hashdata_methods.c
*/

void					*init_hashdata(void);
void					fill_hashdata(void **cell_data, char *path, int number);
void					copy_hashdata(void **cell_data, void *data);
void					clean_hashdata(void *cell_data);
void					print_hashdata(void *cell_data);

/*
** File hash_bash_builtins.c
*/

size_t					btin_hash_valid_argument_add(char *key, void *data);
size_t					btin_hash_valid_argument_delete(char *key);
size_t					btin_hash_list_hashtable(void);
size_t					btin_hash_clean_hashtable(void);
size_t					btin_hash_valid_argument_find(char *key);

/*
** File main_actions.c
*/

int						work_with_add_hash(char *line, int i, int word_beg);
int						work_with_delete_hash(char *line, int i, int word_beg);
int						work_with_find_hash(char *line, int i, int word_beg);
int						work_with_clean_hash(void);
int						work_with_list_hash(void);

/*
** File main_erors.c
*/

int						error_management(char **arg,
							int error, int usage_needed);
int						usage(void);
int						print_help(void);

/*
** File main.c
*/

char					new_norm(char *line, int i, int word_beg);

#endif
