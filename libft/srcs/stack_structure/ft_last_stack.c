/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:58:56 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 18:23:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_last_stack(t_stack **head)
{
	t_stack		*tmp;

	tmp = *head;
	while (tmp && tmp->next && tmp->next->next)
		tmp = tmp->next;
	return (tmp->data);
}
