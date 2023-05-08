/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_call.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:10:44 by egeorgel          #+#    #+#             */
/*   Updated: 2023/05/08 16:46:18 by egeorgel         ###   ########.fr       */
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

static void	access_err(t_data *data, bool is_a_dir)
{
	errno = 0;
	if (is_a_dir)
		exit(1);
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

static bool	check_stat(t_data *data)
{
	struct stat	stats;

	data->cmd_status = 126;
	if (stat(data->lst->str, &stats))
		error_exit(ERRNO, data->lst->str, NULL, data);
	if (S_ISDIR(stats.st_mode) && ft_strchr("./", data->lst->str[0]))
		error_exit(ERR_DIR, data->lst->str, NULL, data);
	else if (S_ISDIR(stats.st_mode))
		return (true);
	return (false);
}

static char	*access_p(t_data *data)
{
	bool	is_a_dir;
	char	*check_path;
	int		i;

	i = -1;
	is_a_dir = check_stat(data);
	if (access(data->lst->str, F_OK) == 0 && !is_a_dir)
		return (ft_strdup(data->lst->str));
	errno = 0;
	if (*data->lst->str == '.' || !data->path)
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
	access_err(data, is_a_dir);
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
