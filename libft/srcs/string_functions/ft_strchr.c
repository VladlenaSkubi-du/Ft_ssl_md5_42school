/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 16:28:33 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 18:53:42 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*new_norm_ternary_return(unsigned char *end, int c)
{
	if (*end == (unsigned char)c)
		return ((char *)end);
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			*iter;
	unsigned char	*end;
	size_t			mask;
	int				i;

	mask = 0;
	i = -1;
	while (++i < (int) sizeof(size_t))
		mask |= ((size_t)(1 + (size_t)c) << ((size_t)i * 8));
	end = (unsigned char *)s;
	while ((size_t)end % sizeof(size_t))
	{
		if (*end == (unsigned char)c || *end == '\0')
			return (new_norm_ternary_return(end, c));
		++end;
	}
	iter = (size_t *)end;
	while (((*iter - mask) & ~(*iter) & 0x8080808080808080) == 0
		&& ((*iter - 0x0101010101010101) & ~(*iter) & 0x8080808080808080) == 0)
		iter++;
	end = (unsigned char *)iter;
	while (*end && *end != (unsigned char)c)
		++end;
	return (new_norm_ternary_return(end, c));
}
