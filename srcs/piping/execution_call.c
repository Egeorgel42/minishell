/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_call.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:10:44 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/10 21:16:07 by egeorgel         ###   ########.fr       */
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

void	excve(char **cmd, t_data *data)
{
	char	*path;

	path = access_p(data);
	if (execve(path, cmd, data->envp) == -1)
		error(ERRNO, NULL, NULL, data);
	free(path);
}

bool	inbuilts(char **cmd, t_data *data)
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
	else if (ft_strcmp(cmd[0], "exit"))
		mini_exit();
	else
		return (false);
	return (true);
}
