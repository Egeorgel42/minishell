/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:32:37 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/29 20:36:06 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipe(t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error_exit(ERRNO, NULL, NULL, data);
	data->pipe_fd = fd[0];
	if (data->out_fd != 1)
		close (data->out_fd);
	data->out_fd = fd[1];
}

static bool	err_redir(t_data *data)
{
	if (!get_redirection_out(data))
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
	if (buf)
		create_pipe(data);
	if (!get_env(data))
	{
		rem_until_rem(&data->lst, buf);
		return ;
	}
	if (!err_redir(data))
		return ;
	remove_quotes(data);
	cmd = get_cmd(data);
	cmd_process(cmd, data);
	rem_until_rem(&data->lst, buf);
	ft_freetab((void *)cmd);
}

void	parent_cmd(t_data *data)
{
	char	**cmd;

	if (!get_env(data) || !get_redirection_out(data))
	{
		ft_lstclear(&data->lst, free);
		return ;
	}
	remove_quotes(data);
	cmd = get_cmd(data);
	if (data->lst && !inbuilts(cmd, data))
		cmd_process(cmd, data);
	ft_lstclear(&data->lst, free);
	ft_freetab((void *)cmd);
	data->status = data->cmd_status;
}

void	wait_pids(t_data *data)
{
	t_pidlst	*buf_pid;

	buf_pid = data->pidlst;
	while (buf_pid)
	{
		waitpid(buf_pid->pid, &data->status, 0);
		buf_pid = buf_pid->next;
	}
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		signal_messages(data, WTERMSIG(data->status));
}
