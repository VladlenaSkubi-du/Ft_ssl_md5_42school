/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_cmd_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:48:11 by sschmele          #+#    #+#             */
/*   Updated: 2021/09/30 22:53:23 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_CMD_LIST_H
# define SSL_CMD_LIST_H

# define SSL_CMDS_NUM 3

static char			*g_sslcmd_list[SSL_CMDS_NUM] = {\
	"md5", \
	"sha256", \
	NULL};

static int			(*g_sslcmd_list_func[SSL_CMDS_NUM])() = {\
	md5_algorithm_start, \
	sha256_algorithm_start, \
	NULL};

#endif