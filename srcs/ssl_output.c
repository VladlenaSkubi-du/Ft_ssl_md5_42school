/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:01:35 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/07 16:33:05 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			ssl_output_algo(char *algo_name)
{
	int		i;

	i = 0;
	while (algo_name[i])
	{
		ft_putchar_fd(ft_toupper(algo_name[i]), STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd(' ', STDOUT_FILENO);
	return (0);
}

size_t		ssl_output_stdin(int flags, char *data, size_t data_type_size)
{
	ft_putstr_fd("(", STDOUT_FILENO);
	if (flags & FLAG_P)
	{
		ft_putstr_fd("\"", STDOUT_FILENO);
		if (data[data_type_size - 1] == '\n')
			ft_putchrstr_fd(data, '\n', STDOUT_FILENO);
		else
			ft_putstr_fd(data, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	else if (flags == 0)
		ft_putstr_fd("stdin", STDOUT_FILENO);
	ft_putstr_fd(") = ", STDOUT_FILENO);
	return (0);
}

/*
** We first send to ssl_get_data 1 as second argument so that in buffer array
** counting starts from 0.
*/

size_t		ssl_output(int flags)
{
	size_t	buf_arguments_size;
	size_t	data_type_size;
	char	*data;
	char	*hash;
	size_t	i;

	ssl_get_dataarray_index(&buf_arguments_size);
	data = ssl_get_data(&data_type_size, 1);
	hash = ssl_get_output(1);
	i = 0;
	while (i < buf_arguments_size && data && hash)
	{
		if (data[0] == STDIN_DATA)
			ssl_output_stdin(flags, data + 1, data_type_size);
		ft_putendl_fd(hash, STDOUT_FILENO);
		data = ssl_get_data(&data_type_size, 0);
		hash = ssl_get_output(0);
		i++;
	}
	return (0);
}