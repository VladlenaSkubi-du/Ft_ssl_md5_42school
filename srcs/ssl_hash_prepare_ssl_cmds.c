/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_prepare_ssl_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:45:42 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/11 13:36:20 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_cmd_list.h"

size_t		ssl_check_command(char *cmd)
{
	size_t	answer_cmd;

	answer_cmd = ssl_save_commands_hashfind(cmd);
	if (answer_cmd == SIZET_MAX)
	{
		ssl_errors_management(ERR_INVALID_CMD, cmd, 0, 0);
		return (SIZET_MAX);
	}
	return (answer_cmd);
}

int			ssl_save_available_commands(void)
{
	int		i;
	size_t	answer;
	void	*cell_data;
	
	i = 0;
	hashtable_init();
	save_clean_hashdata_function(&clean_hashdata);
	while (i < SSL_CMDS_NUM - 1)
	{
		cell_data = init_hashdata();
		if (cell_data == NULL)
			return (ssl_errors_management(ERR_PROGRAMM, NULL, 0, 0));
		fill_hashdata(&cell_data, g_sslcmd_list_options[i],
			g_sslcmd_list_start_func[i]);
		answer = ssl_save_commands_hashadd(g_sslcmd_list[i], cell_data);
		if (answer == SIZET_MAX)
			return (ssl_errors_management(ERR_PROGRAMM, NULL, 0, 0));
		i++;
	}
	ssl_save_commands_hashlist(); //TO DO delete printing
	return (0);
}

int			ssl_clean_saved_commands(void)
{
	hashtable_remove();
	return (0);
}
