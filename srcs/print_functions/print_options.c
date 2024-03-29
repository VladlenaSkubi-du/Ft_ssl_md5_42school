/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:38:49 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/15 00:10:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "print_functions.h"

void		print_options(int flags)
{
	if (flags < 0)
		return ;
	if (flags & FLAG_P)
		ft_putendl_fd("Flag p is activated", STDOUT_FILENO);
	if (flags & FLAG_Q)
		ft_putendl_fd("Flag q is activated", STDOUT_FILENO);
	if (flags & FLAG_S)
		ft_putendl_fd("Flag s is activated", STDOUT_FILENO);
	if (flags & FLAG_R)
		ft_putendl_fd("Flag r is activated", STDOUT_FILENO);
}