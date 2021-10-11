/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:49 by sschmele          #+#    #+#             */
/*   Updated: 2021/10/11 11:53:22 by a18979859        ###   ########.fr       */
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
#include "libft.h"

# define PROGRAM_NAME "./ft_ssl"
# define OPTIONS_NUM 4
# define PROGRAM_OPTIONS "srqp"
# define SSL_ERROR -42

# define STDIN_BUFFER 20
# define FILE_BUFFER 10
# define DATA_BUFFER 3
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
# define HELP_OPTION 0x10000

typedef enum
{
	ERR_OPTION = 0,
	ERR_NO_ARG,
	ERR_MESSAGE_LONG,
	ERR_INVALID_CMD,
	ERR_ALGO,
	ERR_FILEOPEN,
}		t_ssl_errors;

typedef enum
{
	STDIN_DATA = 1,
	STRING_DATA,
	FILE_DATA,
}		t_ssl_messagetype;

typedef struct s_celldata
{
	int		number;
}		t_celldata;


/*
** File ssl_parsing.c
*/

size_t	ssl_parse_arguments(int argc, char **argv, int *flags);

/*
** File ssl_cmd_hashethods.c
*/

size_t	ssl_save_commands_hashlist(void);
size_t	ssl_save_commands_hashadd(char *key);
size_t	ssl_save_commands_hashfind(char *key);
void	clean_hashdata(void *cell_data);
void	print_hashdata(void *cell_data);

/*
** File ssl_error_management.c
*/

int		ssl_errors_management(int error_index, char *arg,
			char end, int usage_needed);
int		ssl_check_posix_option(char *arg, char *options,
			int (error_function)(int error_index, char *arg,
			char end, int usage_needed));

/*
** File ssl_usage.c
*/

void	ssl_usage(void);
void	ssl_usage_cipher_commands(void);
void	ssl_usage_md_commands(void);
void	ssl_usage_standard_commands(void);

/*
** File ssl_message_methods.c
*/

void	ssl_init_data_buffer(void);
void	ssl_save_data(char *data, size_t data_size,
			t_ssl_messagetype type);
size_t	ssl_get_dataarray_index(size_t *data_buffer_size);
char	*ssl_get_data(size_t *data_size, int flag_from_beginning);
void	ssl_free_data(void);


/*
** File ssl_read_message.c
*/

int		ssl_read_from_stdin(void);
int		ssl_read_from_file(int fd, char *data, size_t data_size);

/*
** File ssl_output_results.c
*/

void	ssl_init_output_buffer(void);
void	ssl_save_output(char *output_hash);
char	*ssl_get_output(int flag_from_beginning);
void	ssl_free_output_buffer(void);
int		ssl_output_results(int flags);

int		dgst_start(void);

#endif