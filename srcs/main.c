/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/25 20:51:22 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*ssl_read_from_stdin(size_t *data_size_final)
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
	// if (data_size < 0)
	// 	error("Too long str"); //make an error management
	*data_size_final = data_size;
	return ((data_size + 1 < data_size) ? NULL : data);
}

int		main(int argc, char **argv)
{
	// int		answer;
	// int		flags;
	char		*data;
	size_t		data_size;
	
	// Here we need to check the arguments (empty or not), parse the line to see what algoriphm
	// and options we have. If we have -s option - we take the string, not the stdin
	//
	// if (parse_arguments(argc, argv))
	// 	return (1);
	// flags = ft_find_options(2, (char*[]){PROGRAM_OPTIONS, "--help"}, argv);
	// 	print_options(flags); //TODO delete
	//
	
    // unsigned int i = 1;
    // char *c = (char*)&i;
    // if (*c)    
    //     printf("Little endian");
    // else
    //     printf("Big endian");
    // getchar();
    // return 0;
    
    data_size = 0;
	data = ssl_read_from_stdin(&data_size);
	if (data == NULL)
		return (1);
	// print_bits(data);
    // printf("data_size = %zu\n", data_size);
	md5_algorithm_start(data, data_size);
	free(data);
	return (0);
}
