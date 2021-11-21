/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_smessage_block_methods.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:02:56 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/17 14:30:54 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

static uint32_t	*g_sha256_message_512bit_block;
static size_t	g_sha256_block_number;

int				sha256_init_new_message_block_512bit(uint32_t *message_block,
					size_t block_size)
{
	g_sha256_message_512bit_block = (uint32_t*)ft_xmalloc(sizeof(uint32_t) *
		(block_size + 1));
	ft_memcpy(g_sha256_message_512bit_block, message_block,
		block_size * (sizeof(uint32_t)));
	return (0);
}

uint32_t		*sha256_get_message_512bit_block(void)
{
	return (g_sha256_message_512bit_block);
}

int				sha256_free_new_message_block_512bit(void)
{
	if (g_sha256_message_512bit_block)
		free(g_sha256_message_512bit_block);
	g_sha256_message_512bit_block = NULL;
	return (0);
}

int				sha256_increase_block_number(int clean)
{
	if (clean == 1)
		g_sha256_block_number = 0;
	else
		g_sha256_block_number++;
	return (0);
}

size_t			sha256_get_block_number(void)
{
	return (g_sha256_block_number);
}