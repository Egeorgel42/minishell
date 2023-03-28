/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:07:20 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/28 16:47:38 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child(char **cmd, t_data *data)
{
	update_envp(data);
	dup2(data->in_fd, STDIN_FILENO);
	dup2(data->out_fd, STDOUT_FILENO);
	if (data->lst && !inbuilts(cmd, data))
		excve(cmd, data);
	close(data->in_fd);
	close(data->out_fd);
}

static void	last_child(char **cmd, t_data *data)
{
	update_envp(data);
	dup2(data->in_fd, STDIN_FILENO);
	dup2(data->out_fd, STDOUT_FILENO);
	if (data->lst && !inbuilts(cmd, data))
		excve(cmd, data);
	close(data->in_fd);
	close(data->out_fd);
}

void	cmd_process(char **cmd, t_data *data, bool last)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit(ERRNO, NULL, NULL, data);
	else if (pid == 0 && last)
		last_child(cmd, data);
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
}
