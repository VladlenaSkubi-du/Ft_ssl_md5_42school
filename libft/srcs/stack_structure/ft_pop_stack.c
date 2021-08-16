/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:59:01 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 18:23:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pop_stack(t_stack **head)
{
	int			res;
	t_stack		*tmp;

	tmp = *head;
	if ((*head)->next)
		*head = (*head)->next;
	else
		return (0);
	res = tmp->data;
	free(tmp);
	return (res);
}
