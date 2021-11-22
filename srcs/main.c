/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/22 08:42:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				ssl_main_start(char *algo_name, t_celldata *cmd_data)
{
	int			answer;

	answer = cmd_data->start_algo_function(0);
	if (answer)
	{
		if (answer == -1)
			ssl_errors_management(ERR_ALGO_NOTFOUND, algo_name, 0, 0);
		else if (answer == 1)
			ssl_errors_management(ERR_ALGO, NULL, 0, 0);
		return (1);
	}
	return (0);
}

static int		ssl_prepare_main_environment(void)
{
	ssl_save_available_commands();
	ssl_init_data_buffer();
	return (0);
}

/*
** For debugging:
** print_options(*flags);
** in the end before return (0);
*/

static size_t	ssl_main_actions_with_possible_errors(int argc, char **argv,
					char *algo_name, int *flags)
{
	t_celldata	*cmd_data;
	size_t		answer;

	answer = ssl_check_command(algo_name);
	if (answer == SIZET_MAX)
		return (SIZET_MAX);
	cmd_data = ssl_get_data_from_hashtable(answer);
	if (cmd_data == NULL)
		return (SIZET_MAX);
	answer = ssl_parse_arguments(argc - 1, argv + 1, flags, cmd_data->flags);
	if (answer == SIZET_MAX)
		return (SIZET_MAX);
	ssl_init_output_buffer();
	answer = ssl_main_start(algo_name, cmd_data);
	if (answer)
		return (SIZET_MAX);
	return (0);
}

static int		ssl_clean_main_environment(void)
{
	ssl_free_data_buffer();
	ssl_clean_saved_commands();
	ssl_free_output_buffer();
	return (0);
}

/*
** g_sslcmd_list_start_func[answer_cmd] is the main function call
*/

int				main(int argc, char **argv)
{
	size_t		answer;
	char		*algo_name;
	int			flags;

	if (argc < 2 || !argv[1])
	{
		ssl_usage();
		return (1);
	}
	algo_name = argv[1];
	flags = 0;
	ssl_prepare_main_environment();
	answer = ssl_main_actions_with_possible_errors(argc, argv,
		algo_name, &flags);
	if (answer == SIZET_MAX)
		return (1);
	ssl_output(algo_name, flags);
	ssl_clean_main_environment();
	return (0);
}
