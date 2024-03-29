/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:20:43 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/21 14:41:03 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# define	MD5_NUMBER_OF_ROUNDS			64
# define	MD5_NUMBER_OF_UINT32_VALUES		4
# define	MD5_first_play_min				1
# define	MD5_first_play_max				16
# define	MD5_second_play_min				17
# define	MD5_second_play_max				32
# define	MD5_third_play_min				33
# define	MD5_third_play_max				48
# define	MD5_fourth_play_min				49
# define	MD5_fourth_play_max				64

/*
** File md5_start.c
*/

int			md5_algorithm_start(size_t data_size);

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
** File md5_calculation_algo.c
*/

int			md5_calculate_hash_by_algo(uint32_t *message,
				size_t message_size_uint32);
int			md5_calculate_with_fun_functions(void);
int			md5_play_the_round(uint32_t sum_T_message_by_k,
				uint32_t s_shift,
				uint32_t (*F_fun_function)(uint32_t, uint32_t, uint32_t),
				uint32_t s_shift_index);

/*
** File md5_init_plays.c
*/

int			md5_init_first_play_with_16_rounds(uint32_t round_index,
				uint32_t *message_512bit_block);
int			md5_init_second_play_with_16_rounds(uint32_t round_index,
				uint32_t *message_512bit_block);
int			md5_init_third_play_with_16_rounds(uint32_t round_index,
				uint32_t *message_512bit_block);
int			md5_init_fourth_play_with_16_rounds(uint32_t round_index,
				uint32_t *message_512bit_block);

/*
** File md5_fun_functions.c
*/

uint32_t	md5_fun_first_play(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_fun_second_play(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_fun_third_play(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_fun_fourth_play(uint32_t x, uint32_t y, uint32_t z);

/*
** File md5_svariables_buffer_methods.c
*/

int			md5_init_buffer0_variables(void);
int			md5_init_buffer_variables(void);
int			md5_save_buffer_variables(uint32_t value, int flag);
int			add_to_buffer_variables(uint32_t value, int flag);
uint32_t	md5_get_buffer_variables(int flag);

/*
** File md5_svariables_block_methods.c
*/

int			md5_save_buffer_before_block(void);
int			md5_save_buffer_after_block(void);

/*
** File md5_sconst_and_shift_methods.c
*/

uint32_t	md5_get_shift_first_play_value(size_t index);
uint32_t	md5_get_shift_second_play_value(size_t index);
uint32_t	md5_get_shift_third_play_value(size_t index);
uint32_t	md5_get_shift_fourth_play_value(size_t index);
uint32_t	get_const_table_sin_value(size_t index);

/*
** File md5_smessage_block_methods.c
*/

int			md5_init_new_message_block_512bit(uint32_t *message_block,
				size_t block_size);
uint32_t	*md5_get_message_512bit_block(void);
int			md5_free_new_message_block_512bit(void);
int			md5_increase_block_number(int clean);
size_t		md5_get_block_number(void);

/*
** File md5_output_hash.c (static functions)
*/

int			md5_output_hash(void);

# endif
