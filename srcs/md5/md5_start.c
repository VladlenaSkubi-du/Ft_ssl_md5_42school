/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 17:13:17 by sschmele          #+#    #+#             */
/*   Updated: 2021/04/04 17:50:38 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

int			md5_algorithm(char *data, int data_size)
{
	int		bit_length;
		
	ssl_stdout_data(data, data_size);
	bit_length = data_size * 8;
	prepare_512_blocks(data, bit_length);
	
	return (0);
}