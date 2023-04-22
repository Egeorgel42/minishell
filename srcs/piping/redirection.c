/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:02:51 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/22 18:09:45 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_fd_fill(t_data *data, t_list *buf)
{
	if (ft_strcmp(buf->str, "<<"))
	{
		if (data->in_fd != 0)
			close(data->in_fd);
		if (!heredoc(data, buf->next->str))
			return (2);
	}
	else if (ft_strcmp(buf->str, "<"))
	{
		if (data->in_fd != 0)
			close(data->in_fd);
		data->in_fd = open(buf->next->str, O_RDONLY);
	}
	return (0);
}

static int	redirect_fd(t_data *data, t_list *buf)
{
	if (ft_strcmp(buf->str, ">>"))
	{
		if (data->out_fd != 1)
			close(data->out_fd);
		data->out_fd = open(buf->next->str,
				O_CREAT | O_RDWR | O_APPEND, 000644);
	}
	else if (ft_strcmp(buf->str, ">"))
	{
		if (data->out_fd != 1)
			close(data->out_fd);
		data->out_fd = open(buf->next->str, O_CREAT | O_RDWR | O_TRUNC, 000644);
	}
	else
		if (redirect_fd_fill(data, buf) == 2)
			return (2);
	if (data->in_fd == -1 || data->out_fd == -1)
	{
		error(ERR_FD, buf->next->str, NULL, data);
		return (1);
	}
	return (0);
}

int	get_redirection_out(t_data *data)
{
	t_list	*buf;
	int		err;

	buf = data->lst;
	err = 0;
	while (buf && !strchr("|", *buf->str))
	{
		if (ft_strchr("<>", buf->str[0]))
		{
			if (!buf->next || ft_strchr("<>|", *buf->next->str))
			{
				error(ERR_EMPTY, NULL, buf->str, data);
				err = 2;
			}
			else
				err = redirect_fd(data, buf);
			remove_from_list(&data->lst, buf->next);
			remove_from_list(&data->lst, buf);
			buf = data->lst;
		}
		else if (buf)
			buf = buf->next;
	}
	return (err);
}
