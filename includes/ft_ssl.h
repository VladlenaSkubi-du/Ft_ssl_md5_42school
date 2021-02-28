/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:49 by sschmele          #+#    #+#             */
/*   Updated: 2021/02/28 14:45:33 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <unistd.h>

#include "print_functions.h"
#include "libft.h"

# define PROGRAM_NAME "./ft_ssl"
# define OPTIONS_NUM 4
# define PROGRAM_OPTIONS "pqrs"

# define STDIN_BUFFER 2

# define FLAG_P 0x1
# define FLAG_Q 0x2
# define FLAG_S 0x4
# define FLAG_R 0x8

typedef enum
{
	False = 0,
	True = 1,
}		t_bool;

typedef enum
{
	md5 = 1,
	sha256,
}		t_algtype;

char	*ssl_read_from_stdin(void);
int		ssl_stdout_data(char *data, int data_size);

/*
** File ssl_parsing.c
*/

int		ssl_parse_arguments(int argc, char **argv);

#endif