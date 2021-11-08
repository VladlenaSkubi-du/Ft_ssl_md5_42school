/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:44:10 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/08 20:49:44 by sschmele         ###   ########.fr       */
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

static int	check_algo_options(int argc, char **argv, char *cmd_options)
{
	int		answer;
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

static size_t	error_lets_save_space(t_ssl_errors error, char *option)
{
	ssl_errors_management(error, option, 0, 0);
	return (SIZET_MAX);
}

static size_t	define_default_options(int argc, char **argv, int *flags)
{
	int			i;
	size_t		answer;
	
	i = 0;
	*flags = 0;
	while (argv[++i])
	{
		printf("arg = %s\n", argv[i]);
		if ((!(*flags) || (*flags && !(*flags & FLAG_S) && !(*flags & FLAG_FILENAME)))
				&& argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (error_lets_save_space(ERR_OPTION, "-"));
			else if (argv[i][1] == '-' && !argv[i][2])
				return (error_lets_save_space(ERR_OPTION, "--"));
			else if (argv[i][1] == 'p')
			{
				*flags |= FLAG_P;
				answer = ssl_read_from_stdin();
				if (answer == ERR_MESSAGE_LONG)
					return (error_lets_save_space(ERR_MESSAGE_LONG, NULL));
			}
			else if (argv[i][1] == 'r')
				*flags |= FLAG_R;
			else if (argv[i][1] == 'q')
				*flags |= FLAG_Q;
			else if (argv[i][1] == 's')
			{
				if (!argv[i + 1])
					return (error_lets_save_space(ERR_NO_ARG, NULL));
				*flags |= FLAG_S;		
				answer = ssl_read_string(argv[i + 1]);
				if (answer == ERR_MESSAGE_LONG)
					return (error_lets_save_space(ERR_MESSAGE_LONG, NULL));
				i++;
			}
		}
		else
		{
			*flags |= FLAG_FILENAME;
			answer = ssl_filename_argument(argv[i]);
			if (answer == ERR_FILEOPEN)
				ssl_errors_management(ERR_FILEOPEN, argv[i], 0, 0);
			else if (answer == ERR_MESSAGE_LONG)
				return (error_lets_save_space(ERR_MESSAGE_LONG, NULL));
		}
	}
	if (*flags == 0 || *flags == FLAG_R || *flags == FLAG_Q
			|| (*flags && !(*flags & FLAG_S) && !(*flags & FLAG_FILENAME)))
	{
		answer = ssl_read_from_stdin();
		if (answer == ERR_MESSAGE_LONG)
			return (error_lets_save_space(ERR_MESSAGE_LONG, NULL));
	}
	return (0);
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

size_t	ssl_parse_arguments(int argc, char **argv,
			int *flags, char *cmd_options)
{
	int			i;
	size_t		answer;

	*flags = check_algo_options(argc, argv, cmd_options);
	if (*flags < 0)
		return (SIZET_MAX);
	answer = define_default_options(argc, argv, flags);
	if (answer == SIZET_MAX)
		return (SIZET_MAX);
	// if (*flags & FLAG_R)
	// {
	// 	i = 1;
	// 	while (i < argc && argv[i])
	// 	{
	// 		// printf("argv = %s\n", argv[i]);
	// 		answer = ssl_filename_argument(argv[i]);
	// 		if (answer == ERR_FILEOPEN)
	// 			ssl_errors_management(ERR_FILEOPEN, argv[i], 0, 0);
	// 		else if (answer == ERR_MESSAGE_LONG)
	// 			ssl_errors_management(ERR_MESSAGE_LONG, NULL, 0, 0);
	// 		i++;
	// 	}
	// }
	// answer_other = ssl_read_from_stdin();
	// if (answer_other == ERR_MESSAGE_LONG)
	// {
	// 	ssl_errors_management(ERR_MESSAGE_LONG, NULL, 0, 0);
	// 	return (SIZET_MAX);
	// }
	return (0);
}
