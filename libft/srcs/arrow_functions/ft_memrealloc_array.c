/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:12:43 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/09 21:26:32 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_memrealloc_array(void ***subj, size_t len_subj,
						size_t len_needed)
{
	size_t			i;
	void			**new;
	void			**old;

	i = 0;
	old = *subj;
	new = (void **)ft_xmalloc(sizeof(void *) * (len_needed + 1));
	while (old[i] && i < len_subj)
	{
		new[i] = old[i];
		i++;
	}
	free(*subj);
	return (new);
}
