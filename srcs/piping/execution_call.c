/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_call.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:10:44 by egeorgel          #+#    #+#             */
/*   Updated: 2023/06/05 19:03:38 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool	inbuilts(char **cmd, t_data *data, bool pipe)
{
	data->cmd_status = 0;
	if (ft_strcmp(cmd[0], "pwd"))
		mini_pwd(data);
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
		mini_exit(data, cmd, pipe);
	else
		return (false);
	return (true);
}
