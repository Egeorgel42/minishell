/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:38:51 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/20 12:41:38 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_envp(t_data *data)
{
	t_env	*env;
	char	**up_env;
	int		i;

	env = data->env;
	up_env = malloc(sizeof(char *) * (env_size(env) + 1));
	i = -1;
	while (env)
	{
		up_env[++i] = ft_strdup(env->full_string);
		env = env->next;
	}
	up_env[++i] = NULL;
	if (data->envp)
		ft_freetab((void **)data->envp);
	data->envp = up_env;
	if (data->path)
		ft_freetab((void **)data->path);
	get_path(data);
}

char	**get_cmd(t_data *data)
{
	t_list	*buf;
	char	**cmd;
	int		i;

	buf = data->lst;
	i = 0;
	while (buf && !ft_strcmp(buf->str, "|"))
	{
		buf = buf->next;
		i++;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	buf = data->lst;
	while (buf && !ft_strcmp(buf->str, "|"))
	{
		cmd[i] = ft_strdup(buf->str);
		buf = buf->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

bool	is_flaged(char **str)
{
	if (!str[1])
		return (false);
	if (str[1][0] == '-')
		return (true);
	return (false);
}
