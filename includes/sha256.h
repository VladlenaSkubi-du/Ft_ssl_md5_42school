/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:38:59 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/12 22:56:40 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# define	SHA256_SIZEOF_UINT32_BIT				32
# define	SHA256_NUMBER_OF_ROUNDS					64
# define	SHA256_NUMBER_OF_UINT32_VALUES			8
# define	SHA256_NUMBER_OF_UINT32_VALUES_PARTS	4
# define	SHA256_first_play_min				1
# define	SHA256_first_play_max				16
# define	SHA256_second_play_min				17
# define	SHA256_second_play_max				32
# define	SHA256_third_play_min				33
# define	SHA256_third_play_max				48
# define	SHA256_fourth_play_min				49
# define	SHA256_fourth_play_max				64

/*
** File sha256_start.c
*/

int		sha256_algorithm_start(size_t data_size);

/*
** File sha256_prepare_message.c
*/

uint32_t	*sha256_prepare_message_for_algo(char *data, size_t data_size,
				size_t *message_size_uint32, size_t *mlength_bits_padded);
uint32_t 	*sha256_add_64bit_mlength_to_message(uint32_t *message,
				size_t *message_size_uint32,
				size_t mlength_bits_original, 
				size_t *mlength_bits_padded);
uint32_t 	*sha256_get_64bit_mlength_of_message(
				uint64_t mlength_bits_original,
				size_t uint32_blocks_in_message_add);

/*
** File sha256_output_hash.c
*/

int		sha256_output_hash(void);

# endif