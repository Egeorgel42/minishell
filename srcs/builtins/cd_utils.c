/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:37:08 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/30 15:52:57 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*almost_last_env(t_data *data)
{
	t_env	*env;

	env = data->env;
	if (!env)
		return (NULL);
	if (!env->next)
		return (env);
	while (env->next->next)
		env = env->next;
	return (env);
}

char	*delete_slash(char *str)
{
	int		len;

	len = ft_strlen(str) - 1;
	if (str[len] == '/')
	{
		free(str);
		return (ft_substr(str, 0, len));
	}
	return (str);
}

char	*add_slash(char *str)
{
	if (str[0] != '/')
		str = ft_strjoinfree("/", str, false, false);
	return (str);
}

char	*change_slash(char *str)
{
	int		len;
	char	*buf;

	len = ft_strlen(str) - 1;
	if (str[len] == '/')
	{
		str = ft_substr(str, 0, len);
		if (str[0] != '/')
			str = ft_strjoinfree("/", str, false, true);
	}
	else if (str[0] != '/')
		str = ft_strjoinfree("/", str, false, false);
	buf = ft_strdup(str);
	free(str);
	return (buf);
}

char	*get_pwd(t_data *data, char *dir)
{
	char	*res;

	ft_printf("%d\n",
		"cd: cannot access parent directories: No such file or directory");
	if (*dir == '/')
		res = ft_strdup(dir);
	else
	{
		dir = change_slash(dir);
		res = ft_strjoinfree(data->pwd, dir, false, true);
	}
	return (res);
}

