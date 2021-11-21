/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_compress_64words_block.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:28:08 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/21 17:27:54 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

static uint32_t	sha256_find_temp2_algo(void)
{
	uint32_t	s0;
	uint32_t	maj;
	uint32_t	a;

	a = sha256_get_buffer_variables('a');
	s0 = sha256_find_s0_temp2_algo(a);
	maj = sha256_find_maj_temp2_algo(a);
	return (s0 + maj);
}

/*
** For debug:
** printf("inside t1: h=%u, s1=%u, ch=%u, k[i]=%u, m[i]=%u\n", h, s1, ch,
** k_const, message_64words_block[i]);
*/

static uint32_t	sha256_find_temp1_algo(uint32_t *message_64words_block,
					size_t i)
{
	uint32_t	s1;
	uint32_t	h;
	uint32_t	ch;
	uint32_t	k_const;

	s1 = sha256_find_s1_temp1_algo();
	ch = sha256_find_ch_temp1_algo();
	h = sha256_get_buffer_variables('h');
	k_const = sha256_get_const_table_sin_value(i + 1);
	return (h + s1 + ch + k_const + message_64words_block[i]);
}

/*
** For debug:
**	printf("round %zu\n", i);
** 		printf("t1 = [%u], ", temp1);
**		printf("t2 = [%u], ", temp2);
**		printf("h = [%u], ", sha256_get_buffer_variables('h'));
**		printf("g = [%u], ", sha256_get_buffer_variables('g'));
**		printf("f = [%u], ", sha256_get_buffer_variables('f'));
**		printf("e = [%u], ", sha256_get_buffer_variables('e'));
**		printf("d = [%u], ", sha256_get_buffer_variables('d'));
**		printf("c = [%u], ", sha256_get_buffer_variables('c'));
**		printf("b = [%u], ", sha256_get_buffer_variables('b'));
**		printf("a = [%u]\n\n", sha256_get_buffer_variables('a'));
*/

int				sha256_compress_64_words_block(void)
{
	uint32_t	*message_64words_block;
	size_t		i;
	uint32_t	temp1;
	uint32_t	temp2;
	
	message_64words_block = sha256_get_64words_message_block();
	// if (!message_64words_block || !message_64words_block[0])
	if (!message_64words_block)
		return (0);
	i = 0;
	while (i < SHA256_FULL_NUMBER_OF_WORDS)
	{
		temp1 = sha256_find_temp1_algo(message_64words_block, i);
		temp2 = sha256_find_temp2_algo();
		sha256_save_buffer_variables(sha256_get_buffer_variables('g'), 'h');
		sha256_save_buffer_variables(sha256_get_buffer_variables('f'), 'g');
		sha256_save_buffer_variables(sha256_get_buffer_variables('e'), 'f');
		sha256_save_buffer_variables(sha256_get_buffer_variables('d') + temp1, 'e');
		sha256_save_buffer_variables(sha256_get_buffer_variables('c'), 'd');
		sha256_save_buffer_variables(sha256_get_buffer_variables('b'), 'c');
		sha256_save_buffer_variables(sha256_get_buffer_variables('a'), 'b');
		sha256_save_buffer_variables(temp1 + temp2, 'a');
		i++;
	}
	return (0);
}