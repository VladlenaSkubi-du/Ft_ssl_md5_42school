/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_cmd_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:48:11 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/15 22:16:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_CMD_LIST_H
# define SSL_CMD_LIST_H

# define BUILTINS_NUM 2

static char			*g_sslcmd_list[] = {"md5", NULL};

static int			(*g_sslcmd_list_func[BUILTINS_NUM])() = {\
	md5_algorithm_start, NULL};

#endif