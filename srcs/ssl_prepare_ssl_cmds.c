/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_prepare_ssl_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:45:42 by sschmele          #+#    #+#             */
/*   Updated: 2021/10/28 18:51:19 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_cmd_list.h"

int	ssl_save_available_commands(void)
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
	ssl_save_commands_hashlist(); //TO DO delete printing
	return (0);
}

int	ssl_clean_saved_commands(void)
{
	hashtable_remove();
	return (0);
}