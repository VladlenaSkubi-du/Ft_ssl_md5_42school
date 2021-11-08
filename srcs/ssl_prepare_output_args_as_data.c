/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_prepare_output_args_as_data.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 19:05:02 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/08 12:19:52 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

size_t		ssl_filename_argument(char *filename)
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
	free(filename_in_string);
	if (answer == ERR_MESSAGE_LONG)
	{
		ssl_errors_management(ERR_MESSAGE_LONG, NULL, 0, 0);
		return (SIZET_MAX);
	}
	return (0);
}

/*
** data parameter in the beginning is "filenameSTOP_FILENAME_SEQfile_contents"
** so we look for STOP_FILENAME_SEQ, by finding it we know the end of filename
** data_type_size is found by substracting filename length and
** stop sequence length
*/

char		*interpret_file_data(char *data, size_t *data_type_size, char **filename)
{
	char	*stop_seq_beginning;
	size_t	end_of_filename;
	size_t	stop_seq_length;

	stop_seq_length = ft_strlen(STOP_FILENAME_SEQ);
	stop_seq_beginning = ft_strstr(data, STOP_FILENAME_SEQ);
	if (stop_seq_beginning == NULL)
	{
		*filename = ft_strdup("default_file");
		return (data);
	}
	else
	{
		end_of_filename = stop_seq_beginning - data;
		*filename = ft_strndup(data, end_of_filename);
		*data_type_size = *data_type_size - end_of_filename - stop_seq_length;
	}
	return (data + end_of_filename + stop_seq_length);
}

char		*interpret_file_data_algo(char *data, size_t *data_type_size)
{
	char	*stop_seq_beginning;
	size_t	end_of_filename;
	size_t	stop_seq_length;

	stop_seq_length = ft_strlen(STOP_FILENAME_SEQ);
	stop_seq_beginning = ft_strstr(data + 1, STOP_FILENAME_SEQ);
	if (stop_seq_beginning == NULL)
		return (data);
	else
	{
		end_of_filename = stop_seq_beginning - data;
		*data_type_size = *data_type_size - end_of_filename - stop_seq_length;
	}
	return (data + end_of_filename + stop_seq_length - 1);
}