/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:26:27 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 10:33:30 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*first;

	if (lst == NULL || f == NULL)
		return (NULL);
	new = f(lst);
	first = new;
	lst = lst->next;
	while (lst)
	{
		new->next = f(lst);
		if (!new->next)
		{
			free(new->content);
			free(new->next);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (first);
}
