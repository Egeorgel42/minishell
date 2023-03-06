/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:32:37 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/06 20:50:30 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*access_p(t_data *data, char **path)
{
	char	*check_path;
	int		i;

	i = -1;
	while (path[++i])
	{
		check_path = ft_strjoinfree(path[i], "/", false, false);
		check_path = ft_strjoinfree(check_path, data->lst->str, true, false);
		if (access(check_path, F_OK) == 0)
			return (check_path);
		free(check_path);
	}
	error(ERR_CMD, data->lst->str, NULL, data);
}

static void	child(char **cmd, t_data *data)
{
	char	*path;

	path = access_p(data, path);
	dup2(data->in_fd, STDIN_FILENO);
	dup2(data->out_fd, STDOUT_FILENO);
	update_envp(data);
	if (execve(path, cmd, data->envp) == -1)
		error(ERRNO, NULL, NULL, data);
	free(path);
	close(data->in_fd);
	close(data->out_fd);
}

static void	last_child(char **cmd, t_data *data)
{
	char	*path;

	path = access_p(data, path);
	dup2(data->in_fd, STDIN_FILENO);
	dup2(data->out_fd, STDOUT_FILENO);
	update_envp(data);
	if (execve(path, cmd, data->envp) == -1)
		error(ERRNO, NULL, NULL, data);
	free(path);
	close(data->in_fd);
	close(data->out_fd);
}

static void	cmd_process(t_data *data, bool last)
{
	char	**cmd;

	cmd = get_cmd(data);
	data->pid = fork();
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
}

bool	callstructure(t_data *data)
{
	t_list	*buf;

	buf = data->lst;
	while (buf && !ft_strcmp(buf->str, "|"))
		buf = buf->next;
	if (buf && ft_strcmp(buf->str, "|"))
	{
		create_pipe(data);
		get_redirection_out(data);
		cmd_process(data, false);
		rem_until_rem(&data->lst, buf);
	}
	else if (!buf)
	{
		create_pipe(data);
		get_redirection_out(data);
		cmd_process(data, true);
		ft_lstclear(&data->lst, free);
	}
}
