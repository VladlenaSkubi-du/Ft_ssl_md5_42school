/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_read_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:09:12 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/11 15:37:07 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			ssl_read_from_stdin(void)
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
	{
		free(data);
		return (ERR_MESSAGE_LONG);
	}
	if (data_size > 0)
		ssl_save_data(data, data_size, STDIN_DATA);
	free(data);
	return (0);
}

/*
** In each file we have a filename + its content
** In order to save filename for output and not to mix it
** with the file content, there will be the folliwing
** filling of the string saved:
** _|_|_|_|_|_|_|_|_|_|_|_|_|_|_ ...
** 
** |
** filenamesize
**   |
** filename n bytes
**             |
**           filenamesize
**				 |
**            STOP_FILENAME_SEQ
**                 |
**               file content ...
** In file we can meet any symbol \0 as well so we read
** file untill the function read returns 0
*/

int			ssl_read_from_file(int fd, char *filename_in_string, size_t data_size)
{
	char	buf[FILE_BUFFER];
	char	*data;
	size_t	answer;

	ft_bzero(buf, FILE_BUFFER);
	data = ft_strdup(filename_in_string);
	while ((answer = read(fd, buf, FILE_BUFFER - 1)) > 0)
	{
		data = ft_strrejoin(data, buf);
		data_size += answer;
		ft_bzero(buf, FILE_BUFFER);
	}
	if (data_size + 1 < data_size)
	{
		free(data);
		return (ERR_MESSAGE_LONG);
	}
	ssl_save_data(data, data_size, FILE_DATA);
	free(data);
	return (0);
}

int			ssl_read_string(char *string)
{
	size_t	data_size;

	data_size = ft_strlen(string);
	if (data_size + 1 < data_size)
		return (ERR_MESSAGE_LONG);
	ssl_save_data(string, data_size, STRING_DATA);
	return (0);
}