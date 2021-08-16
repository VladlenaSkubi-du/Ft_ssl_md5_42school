/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:38:27 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 18:20:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_gnl_clean(t_fd_list **p)
{
	t_fd_list	*new;
	t_fd_list	*tmp;

	new = *p;
	while (new)
	{
		tmp = new->next;
		ft_lstclear(&(new->buf));
		free(new);
		new = tmp;
	}
}

static int	new_norm_continuation_get_buf_line(char **line,
				t_fd_list **fd_buf, void *buf, void *p)
{
	if (*(char *)buf != '\0')
		*line = ft_strdup((char *)buf);
	else
		*line = NULL;
	ft_lstclear(&(*fd_buf)->buf);
	(*fd_buf)->index -= (size_t)ft_strlen(*line) + 1;
	if ((*fd_buf)->index > 0)
		(*fd_buf)->buf = ft_lstnew(p + 1, (*fd_buf)->index);
	else
		(*fd_buf)->buf = NULL;
	return (0);
}

int	ft_get_buf_line(char **line, t_fd_list **fd_buf)
{
	void	*p;
	t_list	*start;
	void	*buf;
	int		i;

	i = 0;
	start = (*fd_buf)->buf;
	buf = ft_xmalloc((*fd_buf)->index);
	while (start)
	{
		i += start->content_size;
		ft_memmove(buf + (*fd_buf)->index - i,
			start->content, start->content_size);
		start = start->next;
	}
	ft_memset((p = ft_memchr(buf, 10, (*fd_buf)->index)), 0, 1);
	new_norm_continuation_get_buf_line(line, fd_buf, buf, p);
	free(buf);
	return (1);
}
