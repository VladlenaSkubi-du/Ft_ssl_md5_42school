/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:20:43 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/25 22:40:55 by sschmele         ###   ########.fr       */
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
** File md5_init_variables_functions.c
*/

int			init_buffer_variables(void);

/*
** File md5_svariables_methods.c
*/

int			save_buffer_variables(uint32_t value, int flag);
int			add_to_buffer_variables(uint32_t value, int flag);
int			get_buffer_variables(int flag);

/*
** File md5_fun_functions.c
*/

uint32_t	md5_fun_first_play(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_fun_second_play(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_fun_third_play(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_fun_forth_play(uint32_t x, uint32_t y, uint32_t z);

/*
** File md5_logic_bit_operations.c
*/

uint32_t	md5_bit_and(uint32_t x, uint32_t y);
uint32_t	md5_bit_or(uint32_t x, uint32_t y);
uint32_t	md5_bit_xor(uint32_t x, uint32_t y);

/*
** File md5_sconst_and_shift_methods.c
*/

uint32_t	get_shift_value(size_t index);
uint32_t	get_const_table_sin_value(size_t index);

# endif
