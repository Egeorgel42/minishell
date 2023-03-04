/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:51:04 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/04 17:56:02 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc(t_data *data, char *sep)
{
	char	*tmp;
	char	*str;
	int		fd[2];

	if (pipe(fd) == -1)
		error(ERR_MAX, NULL, NULL, data);
	tmp = NULL;
	str = ft_strjoinfree(sep, "\n", false, false);
	while (!ft_strcmp(tmp, str))
	{
		ft_fprintf(1, "heredoc> ");
		tmp = get_next_line(0);
		if (!ft_strcmp(tmp, str))
			ft_putstr_fd(tmp, fd[1]);
		free(tmp);
	}
	free(str);
	close(fd[1]);
	data->in_fd = fd[0];
}

static void	redirect_fd(t_data *data, t_list *buf)
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
		error(ERR_FD, buf->next->str, NULL, data);
}

void	get_redirection_out(t_data *data)
{
	t_list	*buf;

	buf = data->lst;
	while (buf && !strchr("|", *buf->str))
	{
		if (ft_strchr("<>", buf->str[0]))
		{
			if (!buf->next || ft_strchr("<>|", *buf->next->str))
				error(ERR_EMPTY, NULL, buf->str, data);
			redirect_fd(data, buf);
			remove_from_list(&data->lst, buf->next);
			remove_from_list(&data->lst, buf);
			buf = data->lst;
		}
		if (buf)
			buf = buf->next;
	}
}
