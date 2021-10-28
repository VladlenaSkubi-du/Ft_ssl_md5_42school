/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2021/10/28 19:08:25 by sschmele         ###   ########.fr       */
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

static size_t		ssl_parse_arguments_new(int argc, char **argv)
{
	size_t	answer;
	size_t	i;
	
	if (ft_strcmp(argv[1], "-s") != 0)
	{
		printf("Vlada, make -s string then filename then stdin\n");
		return (0);
	}
	ssl_save_data(argv[2], ft_strlen(argv[2]), STRING_DATA);
	i = 3;
	while (i < argc)
	{
		answer = ssl_filename_argument(argv[i]);
		if (answer == ERR_FILEOPEN)
		{
			ssl_errors_management(ERR_FILEOPEN, argv[3], 0, 0);
			return (SIZET_MAX);
		}
		i++;
	}
	answer = ssl_read_from_stdin();
	if (answer == ERR_MESSAGE_LONG)
	{
		ssl_errors_management(ERR_MESSAGE_LONG, NULL, 0, 0);
		return (SIZET_MAX);
	}
	return (0);
}

static int			print_full_data_saved(void)
{
	size_t			data_size;
	size_t			i;
	char			*data;
	size_t			data_type_size;
	char			*final_data;
	char			*filename;
	
	ssl_get_dataarray_index(&data_size);
	data = ssl_get_data(&data_type_size, 1);
	i = 0;
	while (i < data_size && data)
	{
		if (data[0] == FILE_DATA)
		{
			final_data = interpret_file_data(data + 1, &data_type_size, &filename);
			printf("filename is %s and its contents are \"%s\" with size %zu\n", filename, final_data, data_type_size);
			free(filename);
		}
		if (data[0] == STRING_DATA)
		{
			printf("string is %s with size %zu\n", data + 1, data_type_size);
		}
		else if (data[0] == STDIN_DATA)
		{
			printf("stdin is %s with size %zu\n", data + 1, data_type_size);
		}
		else if (data == NULL)
		{
			printf("something went wrong, there is no data");
			return(0);
		}
		i++;
		data = ssl_get_data(&data_type_size, 0);
	}
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
	ssl_parse_arguments_new(argc, argv);
	// answer_cmd = ssl_parse_arguments(argc, argv + 1, &flags);
	// if (answer_cmd == SIZET_MAX)
	// 	return (1);
	print_full_data_saved();
	// ssl_init_output_buffer();
	// if (g_sslcmd_list_func[answer_cmd] == 1)
	// 	return (ssl_errors_management(ERR_ALGO, NULL, 0, 0));
	// ssl_output_results(flags);
	// ssl_free_output_buffer();
	ssl_free_data();
	// ssl_clean_saved_commands();
	return (0);
}
