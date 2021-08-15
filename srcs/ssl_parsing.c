/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:44:10 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/15 22:27:43 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_cmd_list.h"

static int	ssl_check_if_command(char *cmd_name)
{
	int			i;
	int			answer;

	i = 0;
	while (g_sslcmd_list[i] && g_sslcmd_list_func[i])
	{
		answer = ft_strcmp(cmd_name, g_sslcmd_list[i]);
		if (!answer)
			return (i);
		i++;
	}
	return (-1);
}

static int	ssl_start_command(char *cmd_name, int flags)
{
	int		i;
	int		answer;

	i = 0;
	while (g_sslcmd_list[i])
	{
		answer = ft_strcmp(cmd_name, g_sslcmd_list[i]);
		if (!answer)
		{
			if (flags)
			{
				answer = g_sslcmd_list_func[i]();
				return (answer);
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

/*
** Here we need to check the arguments (empty or not),
** parse the line to see what algoriphm
** and options we have.
** If we have -s option - we take the string, not the stdin
*/

int	ssl_parse_arguments(int argc, char **argv)
{
	int			i;
	int			answer;

	answer = ssl_check_if_command(argv[0]);
	if (answer < 0)
		return (ssl_errors_management(ERR_INVALID_CMD, argv[0], 0, 0));
	i = 0;
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