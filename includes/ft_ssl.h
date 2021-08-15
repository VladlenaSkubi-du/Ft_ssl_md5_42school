/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:49 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/15 15:59:57 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "md5.h"
#include "print_functions.h"
#include "libft.h"

# define PROGRAM_NAME "./ft_ssl"
# define OPTIONS_NUM 4
# define PROGRAM_OPTIONS "srqp"
# define SSL_ERROR -42

# define STDIN_BUFFER 2

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
}		t_ssl_errors;

typedef enum
{
	dgst = 1,
	md5,
	enc,
}		t_ssl_algtype;


/*
** File ssl_parsing.c
*/

int		ssl_parse_arguments(int argc, char **argv);

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

void	ssl_save_data(char *data, size_t data_size);
char	*ssl_get_data(size_t *data_size);
void	ssl_free_data(void);

#endif