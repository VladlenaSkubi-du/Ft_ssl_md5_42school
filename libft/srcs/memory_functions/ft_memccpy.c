/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:18:31 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 11:00:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	size_t			a;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	a = 0;
	d = dst;
	s = (unsigned char *)src;
	while (n--)
	{
		d[i] = s[a];
		if (s[a] == (unsigned char)c)
		{
			i++;
			return (d + i);
		}
		i++;
		a++;
	}
	return (NULL);
}
