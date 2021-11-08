/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:01:35 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/08 21:21:30 by sschmele         ###   ########.fr       */
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

int		ssl_output_string(int flags, char *data)
{
	if (flags && !(flags & FLAG_R))
	{
		ft_putstr_fd("(\"", STDOUT_FILENO);
		ft_putstr_fd(data, STDOUT_FILENO);
		ft_putstr_fd("\") = ", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd(data, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
	return (0);
}

int		ssl_output_file(int flags, char *data, size_t data_type_size)
{
	char	*final_data;
	char	*filename;

	final_data = interpret_file_data(data, &data_type_size, &filename);
	if (flags && !(flags & FLAG_R))
	{
		ft_putstr_fd("(", STDOUT_FILENO);
		ft_putstr_fd(filename, STDOUT_FILENO);
		ft_putstr_fd(") = ", STDOUT_FILENO);
	}
	else
		ft_putendl_fd(filename, STDOUT_FILENO);
	free(filename);
	return (0);
}

int		ssl_output_stdin(int flags, char *data, size_t data_type_size)
{
	if (!flags || (flags && !(flags & FLAG_Q)))
		ft_putstr_fd("(", STDOUT_FILENO);
	if (flags && (flags & FLAG_P))
	{
		ft_putstr_fd("\"", STDOUT_FILENO);
		if (data[data_type_size - 1] == '\n')
			ft_putchrstr_fd(data, '\n', STDOUT_FILENO);
		else
			ft_putstr_fd(data, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	else if (flags == 0 || flags == FLAG_R)
		ft_putstr_fd("stdin", STDOUT_FILENO);
	if (!flags || (flags && !(flags & FLAG_Q)))
		ft_putstr_fd(") = ", STDOUT_FILENO);
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
	// printf("buf_arguments_size = %zu\n", buf_arguments_size);
	data = ssl_get_data(&data_type_size, 1);
	hash = ssl_get_output(1);
	i = 0;
	while (i < buf_arguments_size && data && hash)
	{
		if (flags && (flags & FLAG_Q) && data[0] != STDIN_DATA)
			ft_putendl_fd(hash, STDOUT_FILENO);
		if (data[0] == STDIN_DATA
				&& (!flags || (flags && !(flags & FLAG_Q))))
		{
			ssl_output_algo(algo_name);
			ssl_output_stdin(flags, data + 1, data_type_size);
			ft_putendl_fd(hash, STDOUT_FILENO);
		}
		else if (data[0] == STDIN_DATA
				&& (!flags || (flags && (flags & FLAG_Q) && (flags & FLAG_P))))
		{
			ssl_output_stdin(flags, data + 1, data_type_size);
			ft_putchar_fd('\n', STDOUT_FILENO);
			ft_putendl_fd(hash, STDOUT_FILENO);
		}
		else if (data[0] == STDIN_DATA
				&& (!flags || (flags && (flags & FLAG_Q))))
			ft_putendl_fd(hash, STDOUT_FILENO);
		if (data[0] == FILE_DATA
				&& (flags && !(flags & FLAG_Q) && !(flags & FLAG_R)))
		{
			ssl_output_algo(algo_name);
			ssl_output_file(flags, data + 1, data_type_size);
			ft_putendl_fd(hash, STDOUT_FILENO);
		}
		else if (data[0] == FILE_DATA
				&& (flags && !(flags & FLAG_Q) && (flags & FLAG_R)))
		{
			ft_putstr_fd(hash, STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
			ssl_output_file(flags, data + 1, data_type_size);
		}
		if (data[0] == STRING_DATA
				&& (flags && !(flags & FLAG_Q) && !(flags & FLAG_R)))
		{
			ssl_output_algo(algo_name);
			ssl_output_string(flags, data + 1);
			ft_putendl_fd(hash, STDOUT_FILENO);
		}
		else if (data[0] == STRING_DATA
				&& (flags && !(flags & FLAG_Q) && (flags & FLAG_R)))
		{
			ft_putstr_fd(hash, STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
			ssl_output_string(flags, data + 1);
		}
		// if (!flags
		// 		|| (flags
		// 		&& (!(flags & FLAG_Q) || !(flags & FLAG_R)) || !(flags == FLAG_R)))
		// 	ssl_output_algo(algo_name);
		// if (flags && ((flags & FLAG_R) && !((flags & FLAG_R) && (flags & FLAG_P))))
		// 	ft_putstr_fd(hash, STDOUT_FILENO);
		// if (data[0] == STDIN_DATA && (!flags || !(flags & FLAG_Q)))
		// 	ssl_output_stdin(flags, data + 1, data_type_size);
		// else if (data[0] == FILE_DATA && (!flags || !(flags & FLAG_Q)))
		// 	ssl_output_file(flags, data + 1, data_type_size);
		// else if (data[0] == STRING_DATA && flags && !(flags & FLAG_Q))
		// 	ssl_output_string(flags, data + 1, data_type_size);
		// if (!flags
		// 		|| (flags && (!(flags & FLAG_R)
		// 		|| ((flags & FLAG_R) && (flags & FLAG_P)))))
		// 	ft_putendl_fd(hash, STDOUT_FILENO);
		data = ssl_get_data(&data_type_size, 0);
		hash = ssl_get_output(0);
		i++;
	}
	return (0);
}