/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_logic_bit_operations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:25:41 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/25 22:38:29 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

uint32_t		md5_bit_and(uint32_t x, uint32_t y)
{
	return (x & y);
}

uint32_t		md5_bit_or(uint32_t x, uint32_t y)
{
	return (x | y);
}

uint32_t		md5_bit_xor(uint32_t x, uint32_t y)
{
	return (x ^ y);
}
