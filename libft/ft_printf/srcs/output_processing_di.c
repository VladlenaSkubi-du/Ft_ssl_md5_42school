/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_processing_di.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:30:31 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/09 17:43:12 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flags_ps_or_signs(t_all *all, char *str, int *len)
{
	char	*new;

	if (all->flag_sign_minus == 1 || all->flag_plus == 1
		|| all->flag_space == 1)
	{
		new = ft_strnew((size_t)(*len) + 1);
		++(*len);
	}
	if (all->flag_sign_minus == 1)
		new[0] = '-';
	else if (all->flag_plus == 1)
		new[0] = '+';
	else if (all->flag_space == 1)
		new[0] = ' ';
	else
		return (str);
	ft_strcpy(&new[1], str);
	ft_strdel(&str);
	return (new);
}

char	*int_precision_processing(t_all *all, char *str, int *len)
{
	char	*new;

	new = ft_strnew(all->precision);
	ft_memset((void *)new, '0', (all->precision - *len));
	ft_strcpy(&new[all->precision - *len], str);
	if (all->flag_sign_minus == 1 || all->flag_plus == 1
		|| all->flag_space == 1)
		new = flags_ps_or_signs(all, new, &all->precision);
	*len = all->precision;
	ft_strdel(&str);
	return (new);
}

int	new_norm_ternary_processing_all_width(int all_width, int len)
{
	if (all_width < len)
		return (len);
	return (all_width);
}

char	*int_w_mz_processing(t_all *all, char *str, int *len)
{
	char	*new;
	int		i;

	i = 0;
	if (all->precision < *len && (all->flag_sign_minus == 1
			|| all->flag_plus == 1 || all->flag_space == 1))
	{
		str = flags_ps_or_signs(all, str, len);
		i = 1;
		all->width = new_norm_ternary_processing_all_width(all->width, *len);
	}
	new = ft_strnewsetchar(all->width, ' ');
	if (all->flag_minus == 1)
		ft_memcpy((void *)new, (const void *)str, *len);
	else if (all->flag_zero == 1 && all->precision < 0)
	{
		new[0] = str[0];
		ft_memset((void *)&new[i], '0', (all->width - *len));
		ft_strcpy(&new[all->width - *len + i], &str[i]);
	}
	else
		ft_strcpy(&new[all->width - *len], str);
	*len = all->width;
	ft_strdel(&str);
	return (new);
}
