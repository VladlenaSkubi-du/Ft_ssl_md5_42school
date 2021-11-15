/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:54:41 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/14 12:38:40 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "algorithms.h"

uint32_t		uint32_rotate_left_in_algo(uint32_t value, uint32_t shift)
{
	uint32_t	rotation_done;

	rotation_done = (value << shift) |
		(value >> (SIZEOF_UINT32_BIT - shift));
	return (rotation_done);
}

uint32_t		uint32_rotate_right_in_algo(uint32_t value, uint32_t shift)
{
	uint32_t	rotation_done;

	rotation_done = (value >> shift) |
		(value << (SIZEOF_UINT32_BIT - shift));
	return (rotation_done);
}