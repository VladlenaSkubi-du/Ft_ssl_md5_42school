/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:44:10 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/06 17:04:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_cmd_list.h"

size_t		ssl_check_command(char *cmd)
{
	size_t	answer_cmd;

	answer_cmd = ssl_save_commands_hashfind(cmd);
	if (answer_cmd == SIZET_MAX)
	{
		ssl_errors_management(ERR_INVALID_CMD, cmd, 0, 0);
		return (SIZET_MAX);
	}
	return (answer_cmd);
}

static int	check_program_options(int argc, char **argv)
{
	int		answer;
	int		flags;

	flags = ft_find_options(2, (char*[]){PROGRAM_OPTIONS, "--help"}, argv);
		print_options(flags); // TODO delete
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

/*
** First we check the name of the command we are working with
** Because each command will have its own flags so we check
** it in the beginning
**
** Here we need to check the arguments (empty or not),
** parse the line to see what algoriphm
** and options we have.
** If we have -s option - we take the string, not the stdin
*/

size_t	ssl_parse_arguments(int argc, char **argv, int *flags)
{
	int			i;
	size_t		answer;

	*flags = check_program_options(argc, argv + 1);
	if (*flags < 0)
		return (SIZET_MAX);
	if (*flags == 0)
	{
		answer = ssl_read_from_stdin();
		if (answer == ERR_MESSAGE_LONG)
		{
			ssl_errors_management(ERR_MESSAGE_LONG, NULL, 0, 0);
			return (SIZET_MAX);
		}
	}
	// answer_other = ssl_read_from_stdin();
	// if (answer_other == ERR_MESSAGE_LONG)
	// {
	// 	ssl_errors_management(ERR_MESSAGE_LONG, NULL, 0, 0);
	// 	return (SIZET_MAX);
	// }
	
	// i = 1;
	// while (argv[++i])
	// {
	// 	if (argv[i][0] == '-')
	// 	{
	// 		if (!argv[i][1])
	// 			return (ERR_OPTION);
	// 		else if (argv[i][1] == 'c')
	// 			return ((check_posix_option(argv[i], "c",
	// 				btin_history_error_message) != 0) ?
	// 				BTIN_ERROR : btin_history_clear());
	// 		else if (argv[i][1] == '-' && !argv[i][2])
	// 			return (btin_history_noargs());
	// 	}
	// 	else
	// 		return (btin_history_noargs());
	// }
	return (0);
}
