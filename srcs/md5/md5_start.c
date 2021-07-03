/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:07:56 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/03 17:18:26 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

int			md5_algorithm_start(char *data, int data_size)
{
	int		bit_length;
	int		result;
		
	result = 0;
	ssl_stdout_data(data, data_size);
	bit_length = data_size * 8;
	prepare_512_blocks(data, bit_length);
	return (result);
}