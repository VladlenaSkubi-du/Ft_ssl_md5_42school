/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:06:05 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/11 15:12:32 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			ssl_check_algo_options(int argc, char **argv, char *cmd_options)
{
	int		flags;

	flags = ft_find_options(2, (char*[]){cmd_options, "--help"}, argv);
	if (flags < 0)
	{
		ssl_errors_management(ERR_OPTION, NULL, 0, 0);
		return (-1);
	}
	if (argc == 2 && (flags & FLAG_S))
	{
		ssl_errors_management(ERR_NO_ARG, NULL, 0, 0);
		return (-1);
	}
	return (flags);
}

size_t			ssl_default_options_actions(char **argv, int *i, int *flags)
{
	size_t		answer;

	if (argv[*i][1] == 'p')
	{
		*flags |= FLAG_P;
		answer = ssl_read_from_stdin();
		if (answer == ERR_MESSAGE_LONG)
			return (error_lets_save_space(ERR_MESSAGE_LONG, NULL));
	}
	else if (argv[*i][1] == 'r')
		*flags |= FLAG_R;
	else if (argv[*i][1] == 'q')
		*flags |= FLAG_Q;
	else if (argv[*i][1] == 's')
	{
		if (!argv[*i + 1])
			return (error_lets_save_space(ERR_NO_ARG, NULL));
		*flags |= FLAG_S;		
		answer = ssl_read_string(argv[*i + 1]);
		if (answer == ERR_MESSAGE_LONG)
			return (error_lets_save_space(ERR_MESSAGE_LONG, NULL));
		(*i)++;
	}
	return (0);
}

size_t			ssl_default_fileargs_actions(char **argv, int i, int *flags)
{
	size_t		answer;

	*flags |= FLAG_FILENAME;
	answer = ssl_filename_argument(argv[i]);
	if (answer == ERR_FILEOPEN)
		ssl_errors_management(ERR_FILEOPEN, argv[i], 0, 0);
	else if (answer == ERR_MESSAGE_LONG)
		return (error_lets_save_space(ERR_MESSAGE_LONG, NULL));
	return (0);
}
