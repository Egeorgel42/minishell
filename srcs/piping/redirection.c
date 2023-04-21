/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:51:04 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/21 20:11:05 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_sig	g_sig;

static void	here_child(t_data *data, int *fd, char *sep)
{
	char	*tmp;
	char	*str;

	close(fd[0]);
	tmp = NULL;
	str = NULL;
	while (!ft_strcmp(tmp, sep))
	{
		str = ft_strjoinfree(str, tmp, true, true);
		if (str)
			str = ft_strjoinfree(str, "\n", true, false);
		tmp = readline("heredoc> ");
		if (!tmp)
			break ;
	}
	if (tmp)
		free(tmp);
	developp_env(data, &str);
	ft_putstr_fd(str, fd[1]);
	free(str);
	close(fd[1]);
	exit(0);
}

static bool	heredoc(t_data *data, char *sep)
{
	int		fd[2];
	int		status;

	g_sig.heredoc = true;
	if (pipe(fd) == -1)
		error_exit(ERR_MAX, NULL, NULL, data);
	g_sig.pid = fork();
	if (g_sig.pid == -1)
		error_exit(ERR_MAX, NULL, NULL, data);
	else if (g_sig.pid == 0)
		here_child(data, fd, sep);
	else if (g_sig.pid > 0)
	{
		close(fd[1]);
		if (data->in_fd != 0)
			close(data->in_fd);
		waitpid(g_sig.pid, &status, 0);
		if (!WIFEXITED(status) && WTERMSIG(status) == SIGTERM)
		{
			close (fd[0]);
			data->status = 1;
			return (false);
		}
		data->in_fd = fd[0];
	}
	g_sig.heredoc = false;
	return (true);
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
	else if (ft_strcmp(buf->str, "<<"))
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
