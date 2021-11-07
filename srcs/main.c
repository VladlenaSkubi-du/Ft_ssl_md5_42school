/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/07 14:45:56 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_cmd_list.h"

static size_t		ssl_parse_arguments_new(int argc, char **argv)
{
	size_t	answer;
	int		i;
	
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

static char	*ssl_data_find_filename(char *data_message)
{
	char	*filename;
	char	filename_size;
	int		answer;
	size_t	i;

	filename_size = data_message[1];
	i = 1;
	while (data_message[i])
	{
		if (data_message[i] == filename_size)
		{
			answer = ft_strncmp(data_message + i + 1,
					STOP_FILENAME_SEQ, 5);
			if (answer == 0)
				break ;
		}
		i++;
	}
	filename = ft_strndup(data_message + 2, filename_size);
	return (filename);
}

int		ssl_output_results(void)
{
	char	*data_message;
	char	*filename;
	size_t	needed;
	size_t	i;

	needed = 0;
	data_message = ssl_get_data(&needed, 0);
	while (1)
	{
		if (data_message[0] == FILE_DATA)
			filename = ssl_data_find_filename(data_message);
	}
	free(filename);
	return (0);
}

static int		ssl_main_start(char *algo_name, size_t answer_cmd)
{
	int			answer;
	
	answer = ssl_start_command(algo_name);
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
	ssl_init_output_buffer();
	return (0);
}

static int		ssl_clean_main_environment(void)
{
	ssl_free_output_buffer();
	ssl_free_data_buffer();
	ssl_clean_saved_commands();
	return (0);
}

/*
** g_sslcmd_list_func[answer_cmd] is the main function call
*/

int		main(int argc, char **argv)
{
	size_t	answer_cmd;
	size_t	answer_other;
	char	*algo_name;
	int		flags;

	if (argc == 1)
	{
		ssl_usage();
		return (1);
	}
	algo_name = argv[1];
	ssl_prepare_main_environment();
	answer_cmd = ssl_check_command(algo_name);
	if (answer_cmd == SIZET_MAX)
		return (1);
	answer_other = ssl_parse_arguments(argc, argv + 1, &flags);
	if (answer_other == SIZET_MAX)
		return (1);
	answer_other = ssl_main_start(algo_name, answer_cmd);
	if (answer_other)
		return (1);
	ssl_output_algo(algo_name);
	ssl_output(flags);
	ssl_clean_main_environment();
	return (0);
}
