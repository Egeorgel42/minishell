/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:32:37 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/09 19:46:42 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*access_p(t_data *data)
{
	char	*check_path;
	int		i;

	i = -1;
	while (data->path[++i])
	{
		check_path = ft_strjoinfree(data->path[i], "/", false, false);
		check_path = ft_strjoinfree(check_path, data->lst->str, true, false);
		if (access(check_path, F_OK) == 0)
			return (check_path);
		free(check_path);
	}
	error(ERR_CMD, data->lst->str, NULL, data);
	return (NULL);
}
//path gets also updated on update_envp() (done at start of child)

static void	excve(char **cmd, t_data *data)
{
	char	*path;

	path = access_p(data);
	if (execve(path, cmd, data->envp) == -1)
		error(ERRNO, NULL, NULL, data);
	free(path);
}

static void	inbuilts(char **cmd, t_data *data)
{
	if (ft_strcmp(cmd[0], "pwd"))
		mini_pwd(cmd, data);
	else if (ft_strcmp(cmd[0], "env"))
		mini_env(cmd, data);
	else if (ft_strcmp(cmd[0], "echo"))
		mini_echo(cmd, data);
	else if (ft_strcmp(cmd[0], "export"))
		mini_export(cmd, &data->env, data);
	else if (ft_strcmp(cmd[0], "unset"))
		mini_unset(cmd, &data->env, data);
	else if (ft_strcmp(cmd[0], "cd"))
		mini_cd(cmd, &data->env, data);
	else
		excve(cmd, data);
}

static void	child(char **cmd, t_data *data)
{
	update_envp(data);
	dup2(data->in_fd, STDIN_FILENO);
	dup2(data->out_fd, STDOUT_FILENO);
	inbuilts(cmd, data);
	close(data->in_fd);
	close(data->out_fd);
}

static void	last_child(char **cmd, t_data *data)
{
	update_envp(data);
	dup2(data->in_fd, STDIN_FILENO);
	dup2(data->out_fd, STDOUT_FILENO);
	inbuilts(cmd, data);
	close(data->in_fd);
	close(data->out_fd);
}

static void	cmd_process(t_data *data, bool last)
{
	char	**cmd;

	data->pid = fork();
	cmd = get_cmd(data);
	if (data->pid < 0)
		error(ERRNO, NULL, NULL, data);
	else if (data->pid == 0 && last)
		last_child(cmd, data);
	else if (data->pid == 0)
		child(cmd, data);
	else
	{
		close(data->in_fd);
		data->in_fd = data->out_fd;
	}
	ft_freetab((void **)cmd);
}

void	create_pipe(t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error(ERRNO, NULL, NULL, data);
	data->in_fd = fd[0];
	data->out_fd = fd[1];
}

bool	callstructure(t_data *data)
{
	t_list	*buf;

	data->in_fd = 0;
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
