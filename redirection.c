/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:51:04 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/03 19:13:23 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_data *data, char *sep)
{
	int		fd[2];
	char	*str;

	if (pipe(fd) == -1)
		error(ERR_MAX, NULL, data);
	str = readline("heredoc> ");
	while (!ft_strcmp(str, sep))
	{
		ft_putstr_fd(str, fd[1]);
		str = readline("heredoc> ");
	}
	close(fd[1]);
	data->in_fd = fd[0];
}

void	redirect_fd(t_data *data, t_list *buf)
{
	if (ft_strcmp(buf->str, ">>"))
		data->out_fd = open(buf->next->str, O_CREAT | O_RDWR | O_APPEND, 000644);
	else if (ft_strcmp(buf->str, ">"))
		data->out_fd = open(buf->next->str, O_CREAT | O_RDWR | O_TRUNC, 000644);
	else if (ft_strcmp(buf->str, "<<"))
		heredoc(data, buf->next->str);
	else if (ft_strcmp(buf->str, "<"))
		data->in_fd = open(buf->next->str, O_RDONLY);
	if (data->in_fd == -1 || data->out_fd == -1)
		error(ERR_FD, buf->next->str, data);
}

void	get_redirection_out(t_data *data)
{
	t_list	*buf;

	buf = data->lst;
	while (buf && !strchr("|", *buf->str))
	{
		if (strchr("<>", buf->str[0]))
		{
			if (!buf->next || !buf->next->str || !*buf->next->str
				|| ft_strchr("<>|", *buf->next->str))
				error(ERR_EMPTYREDIRECTION, buf->str, data);
			redirect_fd(data, buf);
			remove_from_list(&data->lst, buf);
			buf = data->lst;
		}
		if (buf)
			buf = buf->next;
	}
}
