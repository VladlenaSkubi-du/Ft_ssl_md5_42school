/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:19:41 by jcorwin           #+#    #+#             */
/*   Updated: 2021/08/16 18:57:26 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	new_norm_ternary_return(char *end, int c, char *s)
{
	if (*end == (char)c)
		return ((int)(end - s));
	return (-1);
}

static int	ft_strchri_mask(size_t *mask, int c)
{
	int				i;

	i = -1;
	while (++i < (int) sizeof(size_t))
		(*mask) |= ((size_t)(1 + (size_t)c) << ((size_t)i * 8));
	return (0);
}

int	ft_strchri(char *s, int c)
{
	size_t			*iter;
	char			*end;
	size_t			mask;

	if (!s || s[0] == '\0')
		return (-1);
	mask = 0;
	ft_strchri_mask(&mask, c);
	end = (char *)s;
	while ((size_t)end % sizeof(size_t))
	{
		if (*end == (unsigned char)c || *end == '\0')
			return (new_norm_ternary_return(end, c, s));
		++end;
	}
	iter = (size_t *)end;
	while (((*iter - mask) & ~(*iter) & 0x8080808080808080) == 0
		&& ((*iter - 0x0101010101010101) & ~(*iter) & 0x8080808080808080) == 0)
		iter++;
	end = (char *)iter;
	while (*end && *end != (char)c)
		++end;
	return (new_norm_ternary_return(end, c, s));
}
