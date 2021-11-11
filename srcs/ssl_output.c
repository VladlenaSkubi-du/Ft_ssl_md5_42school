/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:01:35 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/11 15:29:36 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*g_algo_name;

static int	output_stdin_order(int flags, char *data,
				size_t data_type_size, char *hash)
{
	if (!flags || (flags && !(flags & FLAG_Q)))
	{
		ssl_output_algo(g_algo_name);
		ssl_output_stdin(flags, data + 1, data_type_size);
		ft_putendl_fd(hash, STDOUT_FILENO);
	}
	else if (!flags || (flags && (flags & FLAG_Q) && (flags & FLAG_P)))
	{
		ssl_output_stdin(flags, data + 1, data_type_size);
		ft_putchar_fd('\n', STDOUT_FILENO);
		ft_putendl_fd(hash, STDOUT_FILENO);
	}
	else if (!flags || (flags && (flags & FLAG_Q)))
		ft_putendl_fd(hash, STDOUT_FILENO);
	return (0);
}

static int	output_string_order(int flags, char *data,
				char *hash)
{
	if (flags && !(flags & FLAG_Q) && !(flags & FLAG_R))
	{
		ssl_output_algo(g_algo_name);
		ssl_output_string(flags, data + 1);
		ft_putendl_fd(hash, STDOUT_FILENO);
	}
	else if (flags && !(flags & FLAG_Q) && (flags & FLAG_R))
	{
		ft_putstr_fd(hash, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		ssl_output_string(flags, data + 1);
	}
	return (0);
}

static int	output_file_order(int flags, char *data,
				size_t data_type_size, char *hash)
{
	if (flags && !(flags & FLAG_Q) && !(flags & FLAG_R))
	{
		ssl_output_algo(g_algo_name);
		ssl_output_file(flags, data + 1, data_type_size);
		ft_putendl_fd(hash, STDOUT_FILENO);
	}
	else if (flags && !(flags & FLAG_Q) && (flags & FLAG_R))
	{
		ft_putstr_fd(hash, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		ssl_output_file(flags, data + 1, data_type_size);
	}
	return (0);
}

/*
** We first send to ssl_get_data 1 as second argument so that in buffer array
** counting starts from 0.
*/

size_t		ssl_output(char *algo_name, int flags)
{
	size_t	buf_arguments_size;
	size_t	data_type_size;
	char	*data;
	char	*hash;
	size_t	i;

	ssl_get_dataarray_index(&buf_arguments_size);
	g_algo_name = algo_name;
	data = ssl_get_data(&data_type_size, 1);
	hash = ssl_get_output(1);
	i = -1;
	while (++i < buf_arguments_size && data && hash)
	{
		if (flags && (flags & FLAG_Q) && data[0] != STDIN_DATA)
			ft_putendl_fd(hash, STDOUT_FILENO);
		if (data[0] == STDIN_DATA)
			output_stdin_order(flags, data, data_type_size, hash);
		else if (data[0] == FILE_DATA)
			output_file_order(flags, data, data_type_size, hash);
		else if (data[0] == STRING_DATA)
			output_string_order(flags, data, hash);
		data = ssl_get_data(&data_type_size, 0);
		hash = ssl_get_output(0);
	}
	return (0);
}