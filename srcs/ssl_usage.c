/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 22:59:57 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/28 15:01:05 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

# define MD_COMMANDS_DGST "dgst"
# define MD_COMMANDS_MD5 "md5"
# define MD_COMMANDS_SHA256 "sha256"

void	ssl_usage_standard_commands(void)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ssl_usage_md_commands(void)
{
	ft_putendl_fd(MD_COMMANDS_DGST, STDOUT_FILENO);
	ft_putendl_fd(MD_COMMANDS_MD5, STDOUT_FILENO);
	ft_putendl_fd(MD_COMMANDS_SHA256, STDOUT_FILENO);
}

void	ssl_usage_cipher_commands(void)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
}

/*
** 	ft_printf("(see the `enc' command for more details):\n");
**	ft_printf("%5s%s [command] [--help]\n", "", PROGRAM_NAME);
*/

void	ssl_usage(void)
{
	ft_printf("%s works with standard input and arguments\n", PROGRAM_NAME);
	ft_printf("%s %s command [command options] < STDIN",
		"usage:", PROGRAM_NAME);
	ft_printf(" or %s command [command options] [command arguments]\n",
		PROGRAM_NAME);
	ft_printf("\nStandard commands:\n");
	ssl_usage_standard_commands();
	ft_printf("\nMessage Digest commands ");
	ft_printf("(see the `dgst' command for more details):\n");
	ssl_usage_md_commands();
	ft_printf("\nCipher commands:\n");
	ssl_usage_cipher_commands();
}