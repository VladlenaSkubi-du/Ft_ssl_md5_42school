/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_factorial.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:09:09 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 11:08:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_find_factorial(size_t number)
{
	if (number >= 1)
		return (number * ft_find_factorial(number - 1));
	else
		return (1);
}
