/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:20:43 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/03 18:45:38 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

/*
** File md5_start.c
*/

int			md5_algorithm_start(char *data, size_t data_size);

/*
** File md5_fun_functions.c
*/

int		ssl_fun_first_play(int x, int y, int z);
int		ssl_fun_second_play(int x, int y, int z);
int		ssl_fun_third_play(int x, int y, int z);
int		ssl_fun_forth_play(int x, int y, int z);

/*
** File md5_logic_operations.c
*/

int		ssl_bit_and(int x, int y);
int		ssl_bit_or(int x, int y);
int		ssl_bit_xor(int x, int y);

# endif
