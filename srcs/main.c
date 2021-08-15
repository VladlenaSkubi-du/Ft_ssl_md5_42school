/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/15 15:33:24 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	ssl_read_from_stdin(void)
{
	char	buf[STDIN_BUFFER];
	char	*data;
	size_t	data_size;
	size_t	answer;

	ft_bzero(buf, STDIN_BUFFER);
	data = (char*)ft_xmalloc(1);
	data_size = 0;
	while ((answer = read(STDIN_FILENO, buf, STDIN_BUFFER - 1)) > 0)
	{
		data = ft_strrejoin(data, buf);
		data_size += answer;
		ft_bzero(buf, STDIN_BUFFER);
	}
	if (data_size + 1 < data_size)
		return (ERR_MESSAGE_LONG);
	ssl_save_data(data, data_size);
	return (0);
}

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
		print_options(flags);
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

int		main(int argc, char **argv)
{
	int		answer;
	int		flags;

	flags = check_program_options(argc, argv);
	if (flags == HELP_OPTION)
		return (0);
	else if (flags < 0)
		return (1);
	answer = ssl_parse_arguments(argc, argv + 1);
	// if (answer != 0)
	// 	return (1);
	// if (!(flags & FLAG_S))
	// {
	// 	answer = ssl_read_from_stdin();
	// 	if (answer == ERR_MESSAGE_LONG)
	// 		return (ssl_errors_management(ERR_MESSAGE_LONG, NULL, 0, 0));
	// }
		
	
	// unsigned int i = 1;
	// char *c = (char*)&i;
	// if (*c)    
	//     printf("Little endian");
	// else
	//     printf("Big endian");
	// getchar();
	// return 0;
	
	// if (md5_algorithm_start() == 1)
	// 	return (ssl_errors_management(ERR_ALGO, NULL, 0, 0));
	// ssl_free_data();
	return (0);
}
