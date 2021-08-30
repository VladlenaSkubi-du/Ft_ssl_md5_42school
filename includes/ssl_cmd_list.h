/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_cmd_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:48:11 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/23 11:38:13 by a18979859        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_CMD_LIST_H
# define SSL_CMD_LIST_H

# define SSL_CMDS_NUM 4

static char			*g_sslcmd_list[SSL_CMDS_NUM] = {"dgst", \
	"md5", \
	"sha256", \
	NULL};

static int			(*g_sslcmd_list_func[SSL_CMDS_NUM])() = {\
	dgst_start, \
	md5_algorithm_start, \
	sha256_algorithm_start, \
	NULL};

#endif