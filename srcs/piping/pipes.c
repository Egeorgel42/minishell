/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:32:37 by egeorgel          #+#    #+#             */
/*   Updated: 2023/06/10 18:53:40 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	create_pipe(t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		data->status = 1;
		error(ERRNO, NULL, NULL, data);
		ft_lstclear(&data->lst, free);
		kill_all(data);
		if (data->in_fd != 0)
			close(data->in_fd);
		return (false);
	}
	data->pipe_fd = fd[0];
	if (data->out_fd != 1)
		close (data->out_fd);
	data->out_fd = fd[1];
	return (true);
}

static bool	err_redir(t_data *data, t_list *buf)
{
	int	err;

	err = get_redirection_out(data);
	if (!err)
	{
		if (data->in_fd != 0)
			close (data->in_fd);
		if (data->out_fd != 1)
			close(data->out_fd);
		if (data->pipe_fd != 0)
			close(data->pipe_fd);
		ft_lstclear(&data->lst, free);
		return (false);
	}
	else if (err == -1)
	{
		rem_until_rem(&data->lst, buf);
		return (false);
	}
	return (true);
}

void	callstructure(t_data *data)
{
	char	**cmd;
	t_list	*buf;

	data->pipe_fd = 0;
	data->out_fd = 1;
	buf = data->lst;
	while (buf && !ft_strcmp(buf->str, "|"))
		buf = buf->next;
	if (buf && !create_pipe(data))
		return ;
	if (!get_env(data))
	{
		rem_until_rem(&data->lst, buf);
		return ;
	}
	if (!err_redir(data, buf))
		return ;
	if (empty_pipe(buf, data))
		return ;
	remove_quotes(data);
	cmd = get_cmd(data);
	if (!cmd_process(cmd, data))
		return ;
	rem_until_rem(&data->lst, buf);
	ft_freetab((void *)cmd);
}

void	parent_cmd(t_data *data)
{
	char	**cmd;

	if (!get_env(data) || !err_redir(data, NULL))
	{
		ft_lstclear(&data->lst, free);
		return ;
	}
	remove_quotes(data);
	cmd = get_cmd(data);
	if (data->lst && !inbuilts(cmd, data, false))
	{
		if (!cmd_process(cmd, data))
			return ;
		wait_pids(data);
		ft_lstclear(&data->lst, free);
		ft_freetab((void *)cmd);
		return ;
	}
	ft_lstclear(&data->lst, free);
	ft_freetab((void *)cmd);
	data->status = data->cmd_status;
}

void	wait_pids(t_data *data)
{
	int			stat;
	t_pidlst	*buf_pid;
	bool		did_c;

	did_c = false;
	sigaction(SIGINT, &data->act, NULL);
	buf_pid = data->pidlst;
	while (buf_pid)
	{
		waitpid(buf_pid->pid, &stat, 0);
		buf_pid = buf_pid->next;
		if (!data->get_status)
			continue ;
		else if (WIFEXITED(stat))
			data->status = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat) && WTERMSIG(stat) == SIGINT
			&& !did_c)
		{
			did_c = true;
			ft_printf("\n");
		}
	}
	if (WIFSIGNALED(stat))
		signal_messages(data, WTERMSIG(stat));
}
