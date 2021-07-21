/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:49 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/20 22:06:11 by sschmele         ###   ########.fr       */
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
# define PROGRAM_OPTIONS "pqrs"

# define STDIN_BUFFER 2

# define FLAG_P 0x1
# define FLAG_Q 0x2
# define FLAG_S 0x4
# define FLAG_R 0x8

typedef enum
{
	md5 = 1,
	sha256,
}		t_algtype;


/*
** File ssl_parsing.c
*/

int		ssl_parse_arguments(int argc, char **argv);

#endif