/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_output_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:14:36 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/11 15:46:54 by sschmele         ###   ########.fr       */
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

int			ssl_output_stdin(int flags, char *data, size_t data_type_size)
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

int			ssl_output_string(int flags, char *data)
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

int			ssl_output_file(int flags, char *data, size_t data_type_size)
{
	char	*final_data;
	char	*filename;

	filename = NULL;
	final_data = ssl_interpret_file_data(data, &data_type_size, &filename);
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
