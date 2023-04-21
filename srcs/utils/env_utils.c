/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:37:03 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/21 19:56:35 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_prev_in_env(t_data *data, char *env)
{
	t_env	*buf;

	buf = data->env;
	if (!buf)
		return (NULL);
	while (buf->next && !ft_strcmp(buf->next->pref, env))
		buf = buf->next;
	if (buf->next)
		return (buf);
	return (NULL);
}

t_env	*get_in_env(t_data *data, char *env)
{
	t_env	*buf;

	buf = data->env;
	while (buf && !ft_strcmp(buf->pref, env))
		buf = buf->next;
	if (buf)
		return (buf);
	return (NULL);
}

char	*get_str_env(t_data *data, char *env)
{
	t_env	*buf;

	buf = data->env;
	while (buf && !ft_strcmp(buf->pref, env))
		buf = buf->next;
	if (buf)
		return (ft_strdup(buf->string));
	return (NULL);
}

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
