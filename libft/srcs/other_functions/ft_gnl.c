/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:49:37 by sschmele          #+#    #+#             */
/*   Updated: 2021/08/16 19:00:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define G_SIZE 4096

static t_fd_list	*ft_fd_check(int fd, t_fd_list **p)
{
	t_fd_list	*new;

	if (fd < 0)
	{
		if (fd == GNL_CLEAN)
			ft_gnl_clean(p);
		return (NULL);
	}
	new = *p;
	while (new)
	{
		if (new->fd == fd)
			return (new);
		new = new->next;
	}
	new = (t_fd_list *)ft_xmalloc(sizeof(t_fd_list));
	new->fd = fd;
	new->next = *p;
	return (*p = new);
}

static int	new_norm_continuation_add_tail(int fd, t_fd_list **fd_buf,
				t_list *start, char	buf[G_SIZE])
{
	void	*answer;

	start->content = ft_xmalloc(start->content_size);
	(*fd_buf)->index += start->content_size;
	ft_memmove(start->content, buf, start->content_size);
	answer = ft_memchr(start->content, 10, start->content_size);
	if (!answer)
		return (ft_add_tail(fd, fd_buf));
	return (-42);
}

int	ft_add_tail(int fd, t_fd_list **fd_buf)
{
	t_list	*start;
	int		i;
	char	buf[G_SIZE];

	start = (t_list *)ft_xmalloc(sizeof(t_list));
	ft_lstadd(&(*fd_buf)->buf, start);
	while (1)
	{
		start->content_size = read(fd, buf, G_SIZE);
		if (start->content_size < 1)
			break ;
		i = new_norm_continuation_add_tail(fd, fd_buf, start, buf);
		if (i == -42)
			break ;
		return (i);
	}
	i = start->content_size;
	if (i == 0)
		if (++((*fd_buf)->index))
			ft_memset((start->content = ft_memalloc(++start->content_size)),
				'\n', 1);
	if (i <= 0)
		return (i);
	return (1);
}

static int	new_norm_ternary_ft_gnl(char **line, t_fd_list *fd_buf)
{
	int					answer;

	answer = ft_get_buf_line(line, &fd_buf);
	if (answer == 1)
		return (0);
	return (-1);
}

int	ft_gnl(const int fd, char **line)
{
	static t_fd_list	*fd_list;
	t_fd_list			*fd_buf;
	int					i;

	fd_buf = ft_fd_check(fd, &fd_list);
	if (!fd_buf || read(fd, NULL, 0) || line == NULL)
		return (-1);
	if (fd_buf->buf)
		if (ft_memchr(fd_buf->buf->content, 10, fd_buf->index))
			return (ft_get_buf_line(line, &fd_buf));
	i = ft_add_tail(fd, &fd_buf);
	if (i == 1)
		return (ft_get_buf_line(line, &fd_buf));
	if (i == 0)
		fd_buf->end = 1;
	if (fd_buf->end == 1 && fd_buf->index == 1)
		return (new_norm_ternary_ft_gnl(line, fd_buf));
	if (fd_buf->end == 1 && fd_buf->index != 1)
	{
		ft_memset(fd_buf->buf->content, 10, 1);
		return (ft_get_buf_line(line, &fd_buf));
	}
	return (-1);
}
