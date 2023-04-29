/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:02:51 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/29 19:12:09 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	redirect_fd_fill(t_data *data, t_list *buf)
{
	if (ft_strcmp(buf->str, "<<"))
	{
		if (!heredoc(data, buf->next->str))
			return (false);
	}
	else if (ft_strcmp(buf->str, "<"))
	{
		if (data->in_fd != 0)
			close(data->in_fd);
		data->in_fd = open(buf->next->str, O_RDONLY);
	}
	return (true);
}

static bool	redirect_fd(t_data *data, t_list *buf)
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
		if (!redirect_fd_fill(data, buf))
			return (false);
	if (data->in_fd == -1 || data->out_fd == -1)
	{
		error(ERR_FD, buf->next->str, NULL, data);
		return (false);
	}
	return (true);
}

bool	get_redirection_out(t_data *data)
{
	t_list	*buf;
	bool	err;

	buf = data->lst;
	err = true;
	while (buf && strcmp("|", buf->str))
	{
		if (ft_strchr("<>", buf->str[0]))
		{
			err = redirect_fd(data, buf);
			if (!err)
				break ;
			remove_from_list(&data->lst, buf->next);
			remove_from_list(&data->lst, buf);
			buf = data->lst;
		}
		else if (buf)
			buf = buf->next;
	}
	return (err);
}
