/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2021/10/11 18:52:30 by a18979859        ###   ########.fr       */
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

static size_t		ssl_filename_argument(char *filename)
{
	int		fd;
	char	*filename_in_string;
	size_t	filename_in_string_size;
	size_t	answer;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ERR_FILEOPEN);
	filename_in_string = ft_strjoin(filename, STOP_FILENAME_SEQ);
	filename_in_string_size = ft_strlen(filename) + ft_strlen(STOP_FILENAME_SEQ);
	answer = ssl_read_from_file(fd, filename_in_string, filename_in_string_size);
	if (answer == ERR_MESSAGE_LONG)
	{
		free(filename_in_string);
		ssl_errors_management(ERR_MESSAGE_LONG, NULL, 0, 0);
		return (SIZET_MAX);
	}
	return (0);
}

static size_t		ssl_parse_arguments_new(int argc, char **argv)
{
	size_t	answer;
	
	if (ft_strcmp(argv[1], "-s") != 0)
	{
		printf("Vlada, make -s string then filename then stdin\n");
		return (0);
	}
	ssl_save_data(argv[2], ft_strlen(argv[2]), STRING_DATA);
	answer = ssl_filename_argument(argv[3]);
	if (answer == ERR_FILEOPEN)
	{
		ssl_errors_management(ERR_FILEOPEN, argv[3], 0, 0);
		return (SIZET_MAX);
	}
	answer = ssl_read_from_stdin();
	if (answer == ERR_MESSAGE_LONG)
	{
		ssl_errors_management(ERR_MESSAGE_LONG, NULL, 0, 0);
		return (SIZET_MAX);
	}
	return (0);
}

static char			*interpret_file_data(char *data, size_t *data_type_size, char **filename)
{
	char			*file_contents;
	size_t			end_of_filename;

	end_of_filename = ft_strstr(data, STOP_FILENAME_SEQ) - data; //сделать защиту на NULL
	*filename = ft_strndup(data, end_of_filename);
	*data_type_size = *data_type_size - end_of_filename - ft_strlen(STOP_FILENAME_SEQ);
	return (data + end_of_filename + ft_strlen(STOP_FILENAME_SEQ));
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
	// ssl_save_available_commands();
	ssl_init_data_buffer();
	ssl_parse_arguments_new(argc, argv);
	print_full_data_saved();
	// answer_cmd = ssl_parse_arguments(argc, argv + 1, &flags);
	// if (answer_cmd == SIZET_MAX)
	// 	return (1);
	// ssl_init_output_buffer();
	// if (g_sslcmd_list_func[answer_cmd] == 1)
	// 	return (ssl_errors_management(ERR_ALGO, NULL, 0, 0));
	// ssl_output_results(flags);
	// ssl_free_output_buffer();
	// ssl_free_data();
	// ssl_clean_saved_commands();
	return (0);
}
