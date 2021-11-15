/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:40:12 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/13 23:48:35 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_FUNCTIONS_H
# define PRINT_FUNCTIONS_H

void		print_options(int flags);

/*
** File print_bits_little_endian.c
*/

void        print_bits(char *str);
void		print_bits_as_32uint_little_endian(uint32_t number);
void		print_bits_as_32uint_string_little_endian(uint32_t *message,
				int uint32_blocks);
void		print_bits_as_2_32uint_string_little_endian(uint32_t *message,
				int uint32_blocks);

/*
** File print_bits_big_endian.c
*/

void		print_bits_as_32uint_big_endian(uint32_t number);
void		print_bits_as_32uint_string_big_endian(uint32_t *message,
				int uint32_blocks);
void		print_bits_as_2_32uint_string_big_endian(uint32_t *message,
				int uint32_blocks);

/*
** File md5_print_round_values.c
*/

void		md5_print_description(void);
void		md5_print_ksi(uint32_t k_round_dependent,
				uint32_t s_shift_index,
				uint32_t round_index);
void		md5_print_abcd(void);

/*
** File md5_print_algo_values.c
*/

void		md5_print_message_prepared_in_10(uint32_t *message,
				size_t message_size_uint32);
void		md5_print_message_prepared(uint32_t *message,
				size_t message_size_uint32,
				size_t mlength_bits_padded);

#endif