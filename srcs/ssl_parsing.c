/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:44:10 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/16 22:54:04 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** If there are no flags: ./ft_ssl md5
** or if there are flags but not s and we have not started to see
** all the arguments as filenames: ./ft_ssl md5 -p -r
*/

static int		conditions_for_options(char **argv, int i, int *flags)
{
	if ((!(*flags) || (*flags && !(*flags & FLAG_S)
			&& !(*flags & FLAG_FILENAME)))
			&& argv[i][0] == '-')
		return (1);
	return (0);
}

static size_t	cycle_to_check_arguments(char **argv, int *i, int *flags)
{
	size_t		answer;
	int			conditions;
	
	conditions = conditions_for_options(argv, *i, flags);
	if (conditions)
	{
		if (!argv[*i][1] || (argv[*i][1] && argv[*i][1] == '-' && !argv[*i][2]))
			return (error_lets_save_space(ERR_OPTION, "- or --"));
		else
		{
			answer = ssl_default_options_actions(argv, i, flags);
			if (answer == SIZET_MAX)
				return (SIZET_MAX);
		}
	}
	else
	{
		answer = ssl_default_fileargs_actions(argv, *i, flags);
		if (answer == SIZET_MAX)
			return (SIZET_MAX);
	}
	return (0);
}

/*
** If there are no flags: ./ft_ssl md5
** or there is only r flag: ./ft_ssl md5 -r
** or there is only q flag: ./ft_ssl md5 -q
** or there are flags that are not s and we have not started to
** see all arguments as filenames: ./ft_ssl md5 -q -r -p
*/

static int		conditions_for_stdin(int *flags)
{
	if (*flags == 0 || *flags == FLAG_R || *flags == FLAG_Q
			|| (*flags && !(*flags & FLAG_S) && !(*flags & FLAG_FILENAME)))
		return (1);
	return (0);
}

static size_t	define_default_options(char **argv, int *flags)
{
	int			i;
	int			conditions;
	size_t		answer;
	
	i = 0;
	*flags = 0;
	while (argv[++i])
	{
		// printf("arg = %s\n", argv[i]);
		answer = cycle_to_check_arguments(argv, &i, flags);
		if (answer == SIZET_MAX)
			return (SIZET_MAX);
	}
	conditions = conditions_for_stdin(flags);
	if (conditions)
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
** if we do not have string or -p (that is stdin),
** we have filename arguments
*/

size_t	ssl_parse_arguments(int argc, char **argv,
			int *flags, char *cmd_options)
{
	size_t		answer;

	*flags = ssl_check_algo_options(argc, argv, cmd_options);
	if (*flags < 0)
		return (SIZET_MAX);
	answer = define_default_options(argv, flags);
	if (answer == SIZET_MAX)
		return (SIZET_MAX);
	return (0);
}
