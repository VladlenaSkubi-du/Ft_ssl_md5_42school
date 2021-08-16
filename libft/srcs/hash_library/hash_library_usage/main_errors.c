/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:14:19 by a18979859         #+#    #+#             */
/*   Updated: 2021/08/16 19:02:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash_usage.h"

#define ERRORS_NUM	5

int	print_help(void)
{
	ft_printf("%11s%s [-h]: print help\n", "", PROGRAM_NAME);
	ft_printf("%11s%s [-l]: list all the data keys with data\n", "",
		PROGRAM_NAME);
	ft_printf("%11s%s [-r]: clean the hash table\n", "", PROGRAM_NAME);
	ft_printf("%11s%s [-d key]: delete the key from the hash table\n", "",
		PROGRAM_NAME);
	ft_printf("%11s%s [-f key]: find key index in the hash table\n", "",
		PROGRAM_NAME);
	ft_printf("%11s%s [key]: add the key to the hash table\n", "",
		PROGRAM_NAME);
	return (0);
}

int	usage(void)
{
	ft_printf("%s works with standard input only\n", PROGRAM_NAME);
	ft_printf("usage: %s [-%s] [-%s key] [key] ...\n",
		PROGRAM_NAME, PROGRAM_FLAGS_NO_ARG, PROGRAM_FLAGS_ARG);
	print_help();
	return (0);
}

static char	*errors_messages(int sequence_num)
{
	char		*seq_action[ERRORS_NUM];

	seq_action[0] = "programm error. Sorry. Restart the programm.";
	seq_action[1] = "such key already exists: ";
	seq_action[2] = "hashtable is empty";
	seq_action[3] = "can not find the key: ";
	seq_action[4] = "key is too long: ";
	return (seq_action[sequence_num]);
}

int	error_management(char **arg,
		int error, int arg_print)
{
	char	*error_message;
	char	*arg_ptr;

	if (arg && *arg)
		arg_ptr = *arg;
	else
		arg_ptr = NULL;
	error_message = errors_messages(error);
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	if (arg_ptr && arg_print)
		ft_putendl_fd(arg_ptr, STDERR_FILENO);
	else
		ft_putchar_fd('\n', STDERR_FILENO);
	if (arg && *arg)
	{
		free(*arg);
		arg = NULL;
	}
	return (1);
}
