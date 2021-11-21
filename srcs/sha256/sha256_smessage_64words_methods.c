/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_smessage_64words_methods.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 21:05:14 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/21 14:46:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

static uint32_t	*g_sha256_64words_block;

/*
** We copy each uint32_t word into the new buffer with little-endian to
** big-endian order
**
** For debug:
*/

int			sha256_init_64words_message_block(size_t block_size)
{
	uint32_t	*message_512bit_block;
	size_t		full_words_number_in_block;

	message_512bit_block = sha256_get_message_512bit_block();
	if (!message_512bit_block || !message_512bit_block[0])
		return (1);
	full_words_number_in_block = SHA256_FULL_NUMBER_OF_WORDS;
	g_sha256_64words_block = (uint32_t*)ft_xmalloc(sizeof(uint32_t) *
		(full_words_number_in_block + 1));
	ft_memcpy(g_sha256_64words_block, message_512bit_block,
		block_size * (sizeof(uint32_t)));
	return (0);
}

int			sha256_change_64words_message_block(size_t index,
				uint32_t word_to_change)
{
	g_sha256_64words_block[index] = word_to_change;
	return (0);
}

uint32_t	*sha256_get_64words_message_block(void)
{
	return (g_sha256_64words_block);
}

int			sha256_free_64words_message_block(void)
{
	if (g_sha256_64words_block)
		free(g_sha256_64words_block);
	g_sha256_64words_block = NULL;
	return (0);
}