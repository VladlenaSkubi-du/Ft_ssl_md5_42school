/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_error_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 21:01:57 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/15 15:15:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

#define ERRORS_NUM 5

int	ssl_check_posix_option(char *arg, char *options,
		int (error_function)(int error_index, char *arg,
		char end, int usage_needed))
{
	int				j;
	int				k;
	int				check;

	j = 0;
	check = 0;
	while (arg[++j])
	{
		k = -1;
		check = 0;
		while (options[++k])
		{
			if (arg[j] == options[k])
			{
				check = 1;
				break ;
			}
		}
		if (check == 0)
			return (error_function(ERR_OPTION, NULL, 0, 0));
	}
	return (0);
}

static char	*ssl_errors_types(int sequence_num)
{
	char		*seq_action[ERRORS_NUM];

	seq_action[0] = "invalid option";
	seq_action[1] = "no argument found";
	seq_action[2] = "argument is too long";
	seq_action[3] = "command is invalid: ";
	seq_action[4] = "algorithm error";
	return (seq_action[sequence_num]);
}

int	ssl_errors_management(int error_index, char *arg,
		char end, int usage_needed)
{
	char		*error_message;

	error_message = ssl_errors_types(error_index);
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	if (arg)
	{
		if (arg[0] == end)
		{
			ft_putchar_fd(arg[0], STDERR_FILENO);
			ft_putchrendl_fd(arg + 1, end, STDERR_FILENO);
		}
		else
			ft_putchrendl_fd(arg, end, STDERR_FILENO);
	}
	else
		ft_putchar_fd('\n', STDERR_FILENO);
	if (usage_needed == 1)
		ssl_usage();
	return (-1);
}