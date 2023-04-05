/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_call.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:10:44 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/05 14:51:20 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*access_p(t_data *data)
{
	char	*check_path;
	int		i;

	i = -1;
	if (!data->path)
		error_exit(ERR_CMD, data->lst->str, NULL, data);
	while (data->path[++i])
	{
		check_path = ft_strjoinfree(data->path[i], "/", false, false);
		check_path = ft_strjoinfree(check_path, data->lst->str, true, false);
		if (access(check_path, F_OK) == 0)
			return (check_path);
		free(check_path);
	}
	error_exit(ERR_CMD, data->lst->str, NULL, data);
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
		mini_echo(cmd);
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
