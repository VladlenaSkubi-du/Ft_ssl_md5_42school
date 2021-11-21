/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_compress_64words_block_steps.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:31:09 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/21 14:34:22 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"
#include "algorithms.h"

uint32_t		sha256_find_s1_temp1_algo(void)
{
	uint32_t	first;
	uint32_t	second;
	uint32_t	s1_result;
	uint32_t	e;

	e = sha256_get_buffer_variables('e');
	first = uint32_rotate_right_in_algo(e, SHA256_temp1_s1_efirst_rotright);
	second = uint32_rotate_right_in_algo(e, SHA256_temp1_s1_esecond_rotright);
	s1_result = uint32_bit_xor(first, second);
	first = s1_result;
	second = uint32_rotate_right_in_algo(e, SHA256_temp1_s1_ethird_rotright);
	s1_result = uint32_bit_xor(first, second);
	return (s1_result);
}

uint32_t		sha256_find_ch_temp1_algo(void)
{
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	ch_result;
	
	e = sha256_get_buffer_variables('e');
	f = sha256_get_buffer_variables('f');
	g = sha256_get_buffer_variables('g');
	ch_result = uint32_bit_xor(uint32_bit_and(e, f), uint32_bit_and(~e, g));
	return (ch_result);
}

uint32_t		sha256_find_s0_temp2_algo(uint32_t a)
{
	uint32_t	first;
	uint32_t	second;
	uint32_t	s0_result;

	first = uint32_rotate_right_in_algo(a,
		SHA256_temp2_s0_afirst_rotright);
	second = uint32_rotate_right_in_algo(a,
		SHA256_temp2_s0_asecond_rotright);
	s0_result = uint32_bit_xor(first, second);
	first = s0_result;
	second = uint32_rotate_right_in_algo(a,
		SHA256_temp2_s0_athird_rotright);
	s0_result = uint32_bit_xor(first, second);
	return (s0_result);
}

uint32_t		sha256_find_maj_temp2_algo(uint32_t a)
{
	uint32_t	first;
	uint32_t	second;
	uint32_t	maj_result;
	uint32_t	b;
	uint32_t	c;

	b = sha256_get_buffer_variables('b');
	c = sha256_get_buffer_variables('c');
	first = uint32_bit_and(a, b);
	second = uint32_bit_and(a, c);
	maj_result = uint32_bit_xor(first, second);
	first = maj_result;
	second = uint32_bit_and(b, c);
	maj_result = uint32_bit_xor(first, second);
	return (maj_result);
}
