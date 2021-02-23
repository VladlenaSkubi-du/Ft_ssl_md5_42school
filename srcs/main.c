/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2021/02/23 22:54:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		parse_arguments(int argc, char **argv)
{
	return (0);
}

int		main(int argc, char **argv)
{
	int		answer;
	int		flags;
	
	if (parse_arguments(argc, argv))
		return (1);
	flags = ft_find_options(2, (char*[]){PROGRAM_OPTIONS, "--help"}, argv);
		print_options(flags); //TODO delete
	return (0);
}