/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_call.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:10:44 by egeorgel          #+#    #+#             */
/*   Updated: 2023/05/03 21:52:01 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	test_dirs(t_data *data)
{
	char	**str;
	char	*buf;
	int		i;

	str = ft_split(data->lst->str, '/');
	if (!str || !str[1])
		return ;
	i = 0;
	buf = ft_strdup(str[0]);
	while (str[++i])
	{
		if (access(buf, R_OK) && str[i])
			error_exit(ERR_PERM, data->lst->str, NULL, data);
		buf = ft_strjoinfree(buf, "/", true, false);
		buf = ft_strjoinfree(buf, str[i], true, false);
	}
	ft_freetab((void **)str);
	free(buf);
}

static void	access_err(t_data *data)
{
	errno = 0;
	data->cmd_status = 126;
	if (data->lst->str[ft_strlen(data->lst->str) - 1] == '/')
	{
		if (access(data->lst->str, F_OK) != 0)
			error_exit(ERR_NOT_DIR, data->lst->str, NULL, data);
		error_exit(ERR_DIR, data->lst->str, NULL, data);
	}
	test_dirs(data);
	data->cmd_status = 127;
	if (ft_strchr(data->lst->str, '/'))
		error_exit(ERR_FD, data->lst->str, NULL, data);
	error_exit(ERR_CMD, data->lst->str, NULL, data);
}

static void	check_stat(t_data *data)
{
	struct stat	stats;

	if (stat(data->lst->str, &stats))
		error_exit(ERRNO, NULL, NULL, data);
	data->cmd_status = 126;
	if (S_ISDIR(stats.st_mode))
		error_exit(ERR_DIR, data->lst->str, NULL, data);
}

static char	*access_p(t_data *data)
{
	char	*check_path;
	int		i;

	i = -1;
	if (access(data->lst->str, F_OK) == 0)
	{
		errno = 0;
		check_stat(data);
		return (ft_strdup(data->lst->str));
	}
	if (!data->path)
	{
		errno = 0;
		data->cmd_status = 127;
		error_exit(ERR_FD, data->lst->str, NULL, data);
	}
	while (data->path[++i])
	{
		check_path = ft_strjoinfree(data->path[i], "/", false, false);
		check_path = ft_strjoinfree(check_path, data->lst->str, true, false);
		if (access(check_path, F_OK) == 0)
			return (check_path);
		free(check_path);
	}
	access_err(data);
	return (NULL);
}
//path gets also updated on update_envp() (done at start of child)

void	excve(char **cmd, t_data *data)
{
	char	*path;

	path = access_p(data);
	if (execve(path, cmd, data->envp) == -1)
	{
		free(path);
		if (errno == 13)
			data->cmd_status = 126;
		error_exit(ERRNO, NULL, NULL, data);
	}
}

bool	inbuilts(char **cmd, t_data *data)
{
	data->cmd_status = 0;
	if (ft_strcmp(cmd[0], "pwd"))
		mini_pwd(cmd, data);
	else if (ft_strcmp(cmd[0], "env"))
		mini_env(cmd, data);
	else if (ft_strcmp(cmd[0], "echo"))
		mini_echo(data, cmd);
	else if (ft_strcmp(cmd[0], "export"))
		mini_export(cmd, data);
	else if (ft_strcmp(cmd[0], "unset"))
		mini_unset(data, cmd);
	else if (ft_strcmp(cmd[0], "cd"))
		mini_cd(data, cmd);
	else if (ft_strcmp(cmd[0], "exit"))
		mini_exit(data, cmd);
	else
		return (false);
	return (true);
}
