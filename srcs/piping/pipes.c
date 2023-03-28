/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:32:37 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/28 23:31:27 by egeorgel         ###   ########.fr       */
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
	t_list	*buf;

	data->pipe_fd = 0;
	data->out_fd = 1;
	buf = data->lst;
	while (buf && !ft_strcmp(buf->str, "|"))
		buf = buf->next;
	if (buf && ft_strcmp(buf->str, "|"))
	{
		create_pipe(data);
		if (!get_env(data) || !get_redirection_out(data))
		{
			rem_until_rem(&data->lst, buf);
			return (true);
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

	if (!get_env(data) || !get_redirection_out(data))
	{
		ft_lstclear(&data->lst, free);
		return ;
	}
	get_redirection_out(data);
	remove_quotes(data);
	cmd = get_cmd(data);
	if (data->lst && !inbuilts(cmd, data))
		cmd_process(cmd, data, true);
	ft_lstclear(&data->lst, free);
	ft_freetab((void *)cmd);
}

void	wait_pids(t_data *data)
{
	t_pidlst	*buf_pid;

	buf_pid = data->pidlst;
	while (buf_pid)
	{
		waitpid(buf_pid->pid, NULL, 0);
		buf_pid = buf_pid->next;
	}
}
