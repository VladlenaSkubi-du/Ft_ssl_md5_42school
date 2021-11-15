/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:38:59 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/15 22:00:22 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# define	SHA256_FULL_NUMBER_OF_WORDS				64
# define	SHA256_s0_first_rotright				7
# define	SHA256_s0_second_rotright				18
# define	SHA256_s0_third_shift					3
# define	SHA256_s0_index							15
# define	SHA256_s1_first_rotright				17
# define	SHA256_s1_second_rotright				19
# define	SHA256_s1_third_shift					10
# define	SHA256_s1_index							2
# define	SHA256_word_first_index					16
# define	SHA256_word_second_index				7
# define	SHA256_temp1_s1_efirst_rotright			6
# define	SHA256_temp1_s1_esecond_rotright		11
# define	SHA256_temp1_s1_ethird_rotright			25
# define	SHA256_temp2_s0_afirst_rotright			2
# define	SHA256_temp2_s0_asecond_rotright		13
# define	SHA256_temp2_s0_athird_rotright			22
# define	SHA256_NUMBER_OF_UINT32_VALUES			8
# define	SHA256_NUMBER_OF_UINT32_VALUES_PARTS	4

/*
** File sha256_start.c
*/

int			sha256_algorithm_start(size_t data_size);
int			sha256_calculate_hash_by_algo(uint32_t *message,
				size_t message_size_uint32);

/*
** File sha256_prepare_message.c
*/

uint32_t	*sha256_prepare_message_for_algo(char *data, size_t data_size,
				size_t *message_size_uint32, size_t *mlength_bits_padded);
uint32_t 	*sha256_make_padded_message(char *data, size_t data_size,
				size_t *message_size_uint32,
				size_t mlength_bits_padded);
uint32_t 	*sha256_big_endian_uint32_from_data(char *data, size_t data_size,
				size_t uint32_blocks_in_message);
uint32_t 	*sha256_add_64bit_mlength_to_message(uint32_t *message,
				size_t *message_size_uint32,
				size_t mlength_bits_original, 
				size_t *mlength_bits_padded);
uint32_t 	*sha256_get_64bit_mlength_of_message(
				uint64_t mlength_bits_original,
				size_t uint32_blocks_in_message_add);

/*
** File sha256_smessage_block_methods.c
*/

int			sha256_init_new_message_block_512bit(uint32_t *message_block,
				size_t block_size);
uint32_t	*sha256_get_message_512bit_block(void);
int			sha256_free_new_message_block_512bit(void);
int			sha256_increase_block_number(void);
size_t		sha256_get_block_number(void);

/*
** File sha256_smessage_64words_methods.c
*/

int			sha256_init_64words_message_block(size_t block_size);
int			sha256_change_64words_message_block(size_t index,
				uint32_t word_to_change);
uint32_t	*sha256_get_64words_message_block(void);
int			sha256_free_64words_message_block(void);

/*
** File sha256_prepare_message_schedule.c
*/

int			sha256_make_message_schedule_64words(void);
uint32_t	sha256_find_s1_const(uint32_t *message_64words_block, int i);
uint32_t	sha256_find_s0_const(uint32_t *message_64words_block, int i);

/*
** File sha256_svariables_block_methods.c
*/

int			sha256_save_buffer_before_block(void);
int			sha256_save_buffer_after_block(void);

int			sha256_init_buffer0_variables(void);
int			sha256_init_buffer_variables(void);
int			sha256_save_buffer_variables(uint32_t value, int flag);
int			sha256_add_to_buffer_variables(uint32_t value, int flag);
uint32_t	sha256_get_buffer_variables(int flag);

uint32_t	sha256_get_const_table_sin_value(size_t index);

/*
** File sha256_output_hash.c
*/

int		sha256_output_hash(void);

# endif