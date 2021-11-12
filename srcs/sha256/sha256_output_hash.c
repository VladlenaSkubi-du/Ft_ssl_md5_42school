/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_output_hash.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:03:51 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/12 22:57:28 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

/*
** For debug:
** // printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
** // 	aa&0xff, (aa>>8)&0xff, (aa>>16)&0xff, (aa>>24)&0xff,
** // 	bb&0xff, (bb>>8)&0xff, (bb>>16)&0xff, (bb>>24)&0xff,
** // 	cc&0xff, (cc>>8)&0xff, (cc>>16)&0xff, (cc>>24)&0xff,
** // 	dd&0xff, (dd>>8)&0xff, (dd>>16)&0xff, (dd>>24)&0xff);
** // ft_memcpy((*hash), &aa, 4);
** // ft_memcpy((*hash) + 4, &bb, 4);
** // ft_memcpy((*hash) + 8, &cc, 4);
** // ft_memcpy((*hash) + 12, &dd, 4);
*/

static int	sha256_copy_variables_to_hash(uint8_t **hash)
{
	// uint32_t	value;
	// char		values_order[4] = "abcd";
	// size_t		i;

	// i = 0;
	// while (i < NUMBER_OF_UINT32_VALUES)
	// {
	// 	value = get_buffer_variables(values_order[i]);
	// 	ft_memcpy((*hash) + NUMBER_OF_UINT32_VALUES * i,
	// 		&value, NUMBER_OF_UINT32_VALUES_PARTS);
	// 	i++;
	// }
	return (0);
}

static char	*sha256_make_string_from_hash(uint8_t *hash)
{
	// char	*hash_string;
	// char	hex_char[17] = "0123456789abcdef";
	// size_t	index_in_uint8;
	// size_t	index_in_char;
	// size_t	blocks_in_hash;

	// blocks_in_hash = SHA256_NUMBER_OF_UINT32_VALUES * SHA256_NUMBER_OF_UINT32_VALUES_PARTS;
	// hash_string = (char *)ft_xmalloc(sizeof(char)
	// 	* (blocks_in_hash * 2 + 1));
	// index_in_uint8 = 0;
	// index_in_char = 0;
	// while (index_in_uint8 < 64)
	// {
	// 	hash_string[index_in_char] = hex_char[(hash[index_in_uint8] >> 4) & 0x0F];
	// 	hash_string[index_in_char + 1] = hex_char[hash[index_in_uint8] & 0x0F];
	// 	index_in_uint8++;
	// 	index_in_char += 2;
	// }
	//return (hash_string);
	return (NULL);
}

int sha256_output_hash(void)
{
	// uint8_t		*hash;
	// size_t		blocks_in_hash;
	// char		*hash_string;

	// blocks_in_hash = SHA256_NUMBER_OF_UINT32_VALUES * SHA256_NUMBER_OF_UINT32_VALUES_PARTS;
	// hash = (uint8_t *)ft_xmalloc(sizeof(uint8_t)
	// 	* (blocks_in_hash + 1));
	// sha256_copy_variables_to_hash(&hash);
	// hash_string = sha256_make_string_from_hash(hash);
	// ssl_save_output(hash_string);
	// free(hash);
	return (0);
}
