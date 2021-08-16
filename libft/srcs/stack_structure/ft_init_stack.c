/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:58:50 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 18:23:10 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_init_stack(void)
{
	t_stack			*stack;

	stack = ft_xmalloc(sizeof(t_stack));
	stack->data = 0;
	stack->next = NULL;
	return (stack);
}
