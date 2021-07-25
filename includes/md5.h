/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:20:43 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/24 09:46:57 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

/*
** File md5_start.c
*/

int			md5_algorithm_start(char *data, size_t data_size);

/*
** File md5_prepare_message.c
*/

uint32_t	*md5_prepare_message_for_algo(char *data, size_t data_size,
				size_t *message_size_uint32, size_t *mlength_bits_padded);
size_t		md5_count_message_length_bits_padded(size_t mlength_bits_original);
uint32_t 	*md5_make_padded_message(char *data, size_t data_size,
				size_t *message_size_uint32,
				size_t mlength_bits_padded);
uint32_t 	*md5_add_64bit_mlength_to_message(uint32_t *message,
				size_t *message_size_uint32,
				size_t mlength_bits_original, 
				size_t *mlength_bits_padded);
uint32_t 	*md5_get_64bit_mlength_of_message(
				uint64_t mlength_bits_original,
				size_t uint32_blocks_in_message_add);

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
