/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:32:37 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/31 17:24:17 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipe(t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error_exit(ERRNO, NULL, NULL, data);
	data->pipe_fd = fd[0];
	data->out_fd = fd[1];
}

bool	callstructure(t_data *data)
{
	char	**cmd;
	int		err;
	t_list	*buf;

	data->pipe_fd = 0;
	data->out_fd = 1;
	buf = data->lst;
	while (buf && !ft_strcmp(buf->str, "|"))
		buf = buf->next;
	if (buf && ft_strcmp(buf->str, "|"))
	{
		create_pipe(data);
		if (!get_env(data))
		{
			rem_until_rem(&data->lst, buf);
			return (true);
		}
		err = get_redirection_out(data);
		if (err == 1)
		{
			rem_until_rem(&data->lst, buf);
			return (true);
		}
		else if (err == 2)
		{
			ft_lstclear(&data->lst, free);
			return (false);
		}
		remove_quotes(data);
		cmd = get_cmd(data);
		cmd_process(cmd, data, true);
		rem_until_rem(&data->lst, buf);
		ft_freetab((void *)cmd);
		return (true);
	}
	else if (!buf)
	{
		if (!get_env(data) || !get_redirection_out(data))
		{
			ft_lstclear(&data->lst, free);
			return (false);
		}
		remove_quotes(data);
		cmd = get_cmd(data);
		cmd_process(cmd, data, true);
		ft_lstclear(&data->lst, free);
	}
	ft_freetab((void *)cmd);
	return (false);
}

void	parent_cmd(t_data *data)
{
	char	**cmd;

	if (!get_env(data) || get_redirection_out(data))
	{
		ft_lstclear(&data->lst, free);
		return ;
	}
	remove_quotes(data);
	cmd = get_cmd(data);
	if (data->lst && !inbuilts(cmd, data))
		cmd_process(cmd, data, true);
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
}
