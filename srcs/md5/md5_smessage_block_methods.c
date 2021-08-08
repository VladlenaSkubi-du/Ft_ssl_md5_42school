/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_smessage_block_methods.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 11:26:43 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/08 21:54:42 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static uint32_t	*g_message_512bit_block;
static size_t	g_block_number;

int				init_new_message_block_512bit(uint32_t *message_block,
					size_t block_size)
{
	g_message_512bit_block = (uint32_t*)ft_xmalloc(sizeof(uint32_t) *
		(block_size + 1));
	ft_memcpy(g_message_512bit_block, message_block,
		block_size * (sizeof(uint32_t)));
	return (0);
}

uint32_t		*get_message_512bit_block(void)
{
	return (g_message_512bit_block);
}

int				free_new_message_block_512bit(void)
{
	free(g_message_512bit_block);
	g_message_512bit_block = NULL;
	return (0);
}

int				increase_block_number(void)
{
	g_block_number++;
	return (0);
}

size_t			get_block_number(void)
{
	return (g_block_number);
}