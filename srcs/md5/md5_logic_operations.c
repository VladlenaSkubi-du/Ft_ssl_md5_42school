/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_logic_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:25:41 by sschmele          #+#    #+#             */
/*   Updated: 2021/03/01 11:25:43 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

// Move to libft

int		ssl_bit_and(int x, int y)
{
	return (x & y);
}

int		ssl_bit_or(int x, int y)
{
	return (x | y);
}

int		ssl_bit_xor(int x, int y)
{
	return (x ^ y);
}