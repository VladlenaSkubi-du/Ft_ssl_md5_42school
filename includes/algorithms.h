/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:55:47 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/16 20:41:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

# define	SIZEOF_UINT32_BIT				32
# define	NUMBER_OF_UINT32_VALUES_PARTS	4

/*
** File logic_bit_operations.c
*/

uint32_t		uint32_bit_and(uint32_t x, uint32_t y);
uint32_t		uint32_bit_or(uint32_t x, uint32_t y);
uint32_t		uint32_bit_xor(uint32_t x, uint32_t y);

/*
** File rotations.c
*/

uint32_t		uint32_rotate_left_in_algo(uint32_t value,
					uint32_t s_shift);
uint32_t		uint32_rotate_right_in_algo(uint32_t value, uint32_t shift);


# endif