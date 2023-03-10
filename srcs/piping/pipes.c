/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:32:37 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/10 21:11:01 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipe(t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error(ERRNO, NULL, NULL, data);
	data->pipe_fd = fd[0];
	data->out_fd = fd[1];
}

bool	callstructure(t_data *data)
{
	t_list	*buf;

	data->pipe_fd = 0;
	data->out_fd = 1;
	buf = data->lst;
	while (buf && !ft_strcmp(buf->str, "|"))
		buf = buf->next;
	if (buf && ft_strcmp(buf->str, "|"))
	{
		create_pipe(data);
		get_redirection_out(data);
		cmd_process(data, false);
		rem_until_rem(&data->lst, buf);
		return (true);
	}
	else if (!buf)
	{
		get_redirection_out(data);
		cmd_process(data, true);
		ft_lstclear(&data->lst, free);
	}
	return (false);
}

void	parent_cmd(t_data *data)
{
	char	**cmd;

	get_redirection_out(data);
	cmd = get_cmd(data);
	if (!inbuilts(cmd, data))
		cmd_process(data, true);
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
