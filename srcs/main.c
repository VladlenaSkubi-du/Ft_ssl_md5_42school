/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/24 00:52:43 by a18979859        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_cmd_list.h"

static int	check_program_options(int argc, char **argv)
{
	int		answer;
	int		flags;

	if (argc == 1)
	{
		ssl_usage();
		return (-1);
	}
	flags = ft_find_options(2, (char*[]){PROGRAM_OPTIONS, "--help"}, argv);
		print_options(flags); // TODO delete
	if (flags == HELP_OPTION)
	{
		ssl_usage();
		return (HELP_OPTION);
	}
	else if (flags < 0)
		return (ssl_errors_management(ERR_OPTION, NULL, 0, 0));
	if (argc == 2 && (flags & FLAG_S))
		return (ssl_errors_management(ERR_NO_ARG, NULL, 0, 0));
	return (flags);
}

static int	ssl_save_available_commands(void)
{
	int			i;
	size_t		answer;
	
	i = 0;
	hashtable_init();
	save_clean_hashdata_function(&clean_hashdata);
	while (i < SSL_CMDS_NUM - 1)
	{
		answer = ssl_save_commands_hashadd(g_sslcmd_list[i]);
		if (answer == SIZET_MAX)
			return (0);
		i++;
	}
	ssl_save_commands_hashlist();
	return (0);
}

static int	ssl_clean_saved_commands(void)
{
	hashtable_remove();
	return (0);
}

int		main(int argc, char **argv)
{
	size_t	answer_cmd;
	int		flags;

	flags = check_program_options(argc, argv + 1);
	if (flags == HELP_OPTION)
		return (0);
	else if (flags < 0)
		return (1);
	ssl_save_available_commands();
	ssl_init_data_buffer();
	answer_cmd = ssl_parse_arguments(argc, argv + 1, &flags);
	if (answer_cmd == SIZET_MAX)
		return (1);
	ssl_init_output_buffer();
	if (g_sslcmd_list_func[answer_cmd] == 1)
		return (ssl_errors_management(ERR_ALGO, NULL, 0, 0));
	ssl_output_results(flags);
	
	// unsigned int i = 1;
	// char *c = (char*)&i;
	// if (*c)    
	//     printf("Little endian");
	// else
	//     printf("Big endian");
	// getchar();
	// return 0;
	
	ssl_free_output_buffer();
	ssl_free_data();
	ssl_clean_saved_commands();
	return (0);
}
