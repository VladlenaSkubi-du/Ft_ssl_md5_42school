/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:49 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/28 15:37:40 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>

#include <stdio.h>

#include "md5.h"
#include "sha256.h"
#include "print_functions.h"
#include "algorithms.h"
#include "libft.h"

# define PROGRAM_NAME "./ft_ssl"
# define OPTIONS_NUM 4
# define DEFAULT_ALGO_OPTIONS "srqp"
# define SSL_ERROR -42

# define STDIN_BUFFER 20
# define FILE_BUFFER 10
# define DATA_BUFFER 2
# define STOP_FILENAME_SEQ "\t\v\n\v\t"

/*
** -p: echo STDIN to STDOUT and append the checksum to STDOUT
** Example: $ echo "AA" | ./ft_ssl md5 -p
** AA
** 23...
**
** -q: quiet mode
**
** -r: reverse the format of the output
**
** -s: print the sum of the given string
*/

# define FLAG_P 0x1
# define FLAG_Q 0x2
# define FLAG_R 0x4
# define FLAG_S 0x8
# define FLAG_FILENAME 0x10
# define HELP_OPTION 0x10000

typedef enum
{
	ERR_OPTION = 0,
	ERR_NO_ARG,
	ERR_MESSAGE_LONG,
	ERR_INVALID_CMD,
	ERR_ALGO,
	ERR_ALGO_NOTFOUND,
	ERR_FILEOPEN,
	ERR_PROGRAMM,
}		t_ssl_errors;

typedef enum
{
	STDIN_DATA = 1,
	STRING_DATA,
	FILE_DATA,
}		t_ssl_messagetype;

typedef struct s_celldata
{
	char		*flags;
	int			(*start_algo_function)(size_t);
}		t_celldata;


int			dgst_start(size_t data);
int			dgst_output(void);

/*
** File main.c (static functions)
*/

int			ssl_main_start(char *algo_name, t_celldata *cmd_data);

/*
** File ssl_hash_prepare_ssl_cmds.c
*/

size_t		ssl_check_command(char *cmd);
int			ssl_save_available_commands(void);
int			ssl_clean_saved_commands(void);

/*
** File ssl_hash_cmd_hashethods.c
*/

size_t		ssl_save_commands_hashlist(void);
size_t		ssl_save_commands_hashadd(char *key, void *data);
size_t		ssl_save_commands_hashfind(char *key);
t_celldata	*ssl_get_data_from_hashtable(size_t answer_cmd);

/*
** File ssl_hash_hashdata_methods.c
*/

void		*init_hashdata(void);
void		fill_hashdata(void **cell_data, char *options,
				int (*start_algo_function)(size_t));
void		copy_hashdata(void **cell_data, void *data);
void		clean_hashdata(void *cell_data);
void		print_hashdata(void *cell_data);

/*
** File ssl_message_methods.c
*/

void		ssl_init_data_buffer(void);
void		ssl_save_data(char *data, size_t data_size,
				t_ssl_messagetype type);
size_t		ssl_get_dataarray_index(size_t *data_buffer_size);
char		*ssl_get_data(size_t *data_size, int flag_from_beginning);
char		*ssl_get_data_algo(size_t *data_size, int flag_from_beginning);
void		ssl_free_data_buffer(void);

/*
** File ssl_parsing.c (static functions)
*/

size_t		ssl_parse_arguments(int argc, char **argv,
				int *flags, char *cmd_options);

/*
** File ssl_options.c
*/

int			ssl_check_algo_options(int argc, char **argv, char *cmd_options);
size_t		ssl_default_options_actions(char **argv, int *i, int *flags);
size_t		ssl_default_fileargs_actions(char **argv, int i, int *flags);

/*
** File ssl_read_message.c
*/

int			ssl_read_from_stdin(void);
int			ssl_read_from_file(int fd, char *data, size_t data_size);
int			ssl_read_string(char *string);

/*
** File ssl_read_filename.c
*/

size_t		ssl_filename_argument(char *filename);
char		*ssl_interpret_file_data(char *data, size_t *data_type_size,
			char **filename);
char		*ssl_interpret_file_data_algo(char *data, size_t *data_type_size);

/*
** File ssl_output.c (static functions)
*/

size_t		ssl_output(char *algo_name, int flags);

/*
** File ssl_output_options.c
*/

int			ssl_output_algo(char *algo_name);
int			ssl_output_stdin(int flags, char *data, size_t data_type_size);
int			ssl_output_string(int flags, char *data);
int			ssl_output_file(int flags, char *data, size_t data_type_size);

/*
** File ssl_soutput_buffer_methods.c
*/

void		ssl_init_output_buffer(void);
void		ssl_save_output(char *output_hash);
char		*ssl_get_output(int flag_from_beginning);
void		ssl_free_output_buffer(void);

/*
** File ssl_error_management.c
*/

int			ssl_errors_management(int error_index, char *arg,
				char end, int usage_needed);
int			ssl_check_posix_option(char *arg, char *options,
				int (error_function)(int error_index, char *arg,
				char end, int usage_needed));
size_t		error_lets_save_space(t_ssl_errors error, char *option);

/*
** File ssl_usage.c
*/

void		ssl_usage(void);
void		ssl_usage_cipher_commands(void);
void		ssl_usage_md_commands(void);
void		ssl_usage_standard_commands(void);

#endif