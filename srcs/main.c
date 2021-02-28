/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2021/02/28 14:51:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		ssl_stdout_data(char *data, int data_size)
{
	// make conditions if flags are special
	write(STDOUT_FILENO, data, data_size);
	return (0);
}

char	*ssl_read_from_stdin(void)
{
	char	buf[STDIN_BUFFER];
	char	*data;
	int		data_size;
	int		answer;

	ft_bzero(buf, STDIN_BUFFER);
	data = (char*)ft_xmalloc(1);
	data_size = 0;
	while ((answer = read(STDIN_FILENO, buf, STDIN_BUFFER - 1)) > 0)
	{
		data = ft_strrejoin(data, buf);
		data_size += answer;
		ft_bzero(buf, STDIN_BUFFER);
	}
	// if (data_size < 0)
	// 	error("Too long str"); //make an error management
	ssl_stdout_data(data, data_size);
	return ((data_size < 0) ? NULL : data);
}

int		main(int argc, char **argv)
{
	// int		answer;
	// int		flags;
	char		*data;
	
	// Here we need to check the arguments (empty or not), parse the line to see what algoriphm
	// and options we have. If we have -s option - we take the string, not the stdin
	//
	// if (parse_arguments(argc, argv))
	// 	return (1);
	// flags = ft_find_options(2, (char*[]){PROGRAM_OPTIONS, "--help"}, argv);
	// 	print_options(flags); //TODO delete
	//
	data = ssl_read_from_stdin();
	if (data == NULL)
		return (1);
	print_bits(data);
	return (0);
}