/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dgst_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 00:31:40 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/28 15:36:32 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	print_default_options(void)
{
	char	*p;
	char	*q;
	char	*r;
	char	*s;

	p = "to echo STDIN to STDOUT and append the checksum to STDOUT";
	q = "to activate quiet mode";
	r = "to activate reverse the format of the output";
	s = "to print the sum of the given string";
	ft_printf("\n%5.5s %.100s", "-p", p);
	ft_printf("\n%5.5s %.100s", "-q", q);
	ft_printf("\n%5.5s %.100s", "-r", r);
	ft_printf("\n%5.5s %.100s\n", "-s", s);
	return (0);
}

int		dgst_start(size_t data)
{
	if (data)
		return (0);
	ft_printf("\nMessage Digest commands:\n");
	ssl_usage_md_commands();
	ft_printf("\nMessage Digest commands have the following options:");
	ft_printf("\nmd5:");
	print_default_options();
	ft_printf("\nsha256:");
	print_default_options();
	return(0);
}

int		dgst_output(void)
{
	return (0);
}