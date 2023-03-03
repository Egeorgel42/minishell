/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:32:37 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/03 22:57:49 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*access_p(t_data *data, char **path, char *cmd)
{
	char	*check_path;
	int		i;

	i = -1;
	while (path[++i])
	{
		check_path = ft_strjoinfree(path[i], "/", false, false);
		check_path = ft_strjoinfree(check_path, cmd, true, false);
		if (access(check_path, F_OK) == 0)
			return (check_path);
		free(check_path);
	}
	error(ERR_CMD, cmd, data);
}

void	child(int *fd, int fd_tmp, char **cmd, t_data *data)
{
	char	*path;

	path = access_p(data, path, *cmd);
	dup2(fd_tmp, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (execve(path, cmd, data->envp) == -1)
		error(ERR_EXC, NULL, data);
	free(path);
	close(fd_tmp);
	close(fd[1]);
	close(fd[0]);
}

void	last_child(int *fd, int *fd_tmp, char **cmd, t_data *data)
{
	char	*path;

	path = access_p(data, path, *cmd);
	dup2(fd_tmp[0], STDIN_FILENO);
	dup2(fd_tmp[1], STDOUT_FILENO);
	if (execve(path, cmd, data->envp) == -1)
		error(ERR_EXC, NULL, data);
	free(path);
	close(fd_tmp[0]);
	close(fd_tmp[1]);
	close(fd[1]);
	close(fd[0]);
}

int	pipe_loop(int *fd_tmp, char **cmd, t_data *data, bool last)
{
	int		fd[2];

	if (pipe(fd) == -1)
		error(ERRNO, NULL, data);
	data->pid = fork();
	if (data->pid < 0)
		error(ERRNO, NULL, data);
	else if (data->pid == 0 && last)
		last_child(fd, fd_tmp, cmd, data);
	else if (data->pid == 0)
		child(fd, *fd_tmp, cmd, data);
	else
	{
		close(fd[1]);
		return (fd[0]);
	}
	return (0);
}

void	pipes(t_data *data)
{
	int		fd_tmp[2];
	int		i;

	i = -1;
	while (data->pipe_str[++i])
	{
		fd_tmp[0] = data->in_fd;
		if (i == data->max_cmd - 1)
		{
			fd_tmp[1] = data->out_fd;
			data->in_fd = pipe_loop(fd_tmp, data->cmd[i], data, true);
		}
		else
			data->in_fd = pipe_loop(fd_tmp, data->cmd[i], data, false);
		close(fd_tmp[0]);
	}
	close(data->out_fd);
	close(data->in_fd);
	close(fd_tmp[1]);
	waitpid(data->pid, NULL, 0);
}