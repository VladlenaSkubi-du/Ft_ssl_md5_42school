/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 22:10:11 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 19:26:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash_usage.h"

char	new_norm(char *line, int i, int word_beg)
{
	if (line[i] == ' ')
		return (i - word_beg);
	return (i + 1 - word_beg);
}

static int	route_builtins(char *line, int i, int word_beg, int flag)
{
	if (flag == FLAG_R && i == 1)
		work_with_clean_hash();
	else if (flag == FLAG_L && i == 1)
		work_with_list_hash();
	else if (flag == FLAG_H && i == 1)
		print_help();
	else if ((flag == FLAG_R || flag == FLAG_L || flag == FLAG_H) && i > 1)
		return (0);
	else if (flag == FLAG_F)
		work_with_find_hash(line, i, word_beg);
	else if (flag == FLAG_D)
		work_with_delete_hash(line, i, word_beg);
	else
		work_with_add_hash(line, i, word_beg);
	return (0);
}

static int	work_with_command_line(char *line, int i,
				int word_beg, int flag)
{
	while (line[i])
	{
		if (i == 0 && line[i] == '-' && line[i + 1])
		{
			if (line[i + 1] == 'd')
				flag = FLAG_D;
			else if (line[i + 1] == 'r')
				flag = FLAG_R;
			else if (line[i + 1] == 'l')
				flag = FLAG_L;
			else if (line[i + 1] == 'f')
				flag = FLAG_F;
			else if (line[i + 1] == 'h')
				flag = FLAG_H;
			i++;
		}
		if (line[i] == ' ' || line[i + 1] == 0)
		{
			route_builtins(line, i, word_beg, flag);
			word_beg = i + 1;
		}
		i++;
	}
	return (0);
}

static int	read_from_user(void)
{
	char	*line;
	int		i;
	int		word_beg;
	int		flag;

	line = NULL;
	flag = 0;
	while (ft_gnl(0, &line))
	{
		if (!line || !line[0])
		{
			ft_printf("Please, enter key words\n");
			usage();
			continue ;
		}
		i = 0;
		word_beg = i;
		work_with_command_line(line, i, word_beg, flag);
		free(line);
		line = NULL;
		flag = 0;
	}
	ft_gnl(GNL_CLEAN, NULL);
	return (0);
}

int	main(void)
{
	hashtable_init();
	save_clean_hashdata_function(&clean_hashdata);
	read_from_user();
	hashtable_remove();
	return (0);
}
