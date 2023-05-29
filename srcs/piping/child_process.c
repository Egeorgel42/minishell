/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:07:20 by egeorgel          #+#    #+#             */
/*   Updated: 2023/05/29 19:12:07 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child(char **cmd, t_data *data)
{
	update_envp(data);
	dup2(data->in_fd, STDIN_FILENO);
	dup2(data->out_fd, STDOUT_FILENO);
	if (data->pipe_fd != 0)
		close(data->pipe_fd);
	if (data->lst && !inbuilts(cmd, data))
		excve(cmd, data);
	if (data->in_fd != 0)
		close(data->in_fd);
	if (data->out_fd != 0)
		close(data->out_fd);
	exit(data->cmd_status);
}

bool	cmd_process(char **cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		error(ERRNO, NULL, NULL, data);
		ft_lstclear(&data->lst, free);
		ft_freetab((void *)cmd);
		kill_all(data);
		return (false);
	}
	else if (pid == 0)
		child(cmd, data);
	else
	{
		if (data->in_fd != 0)
			close(data->in_fd);
		if (data->out_fd != 1)
			close(data->out_fd);
		data->in_fd = data->pipe_fd;
		add_pid(pid, data);
	}
	return (true);
}

void	kill_all(t_data *data)
{
	t_pidlst	*pidlst;

	pidlst = data->pidlst;
	while (pidlst)
	{
		kill(pidlst->pid, SIGTERM);
		pidlst = pidlst->next;
	}
}
