/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:37:03 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/20 12:40:34 by vkuzmin          ###   ########.fr       */
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

void	start_pwd(t_data *data)
{
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
		error_exit(ERR_START_PWD, NULL, NULL, data);
}

/*need upgrade*/
void	ft_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(1);
}

void	get_path(t_data *data)
{
	t_env	*env;

	env = get_in_env(data, "PATH");
	if (!env)
		data->path = NULL;
	else
		data->path = ft_split(env->string, ':');
}
