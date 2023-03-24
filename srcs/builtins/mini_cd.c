/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:00:06 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/24 17:24:37 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	full_change(char *dir, t_env **env)
{
	t_env	*current;

	current = *env;
	while (ft_strncmp(current->pref, "PWD", 3))
		current = current->next;
	free(current->full_string);
	current->full_string = ft_strjoin("PWD=", dir);
	free(current->string);
	current->string = dir;
}

static void	small_change(char *dir, t_env **env)
{
	t_env	*current;
	char	*str;

	current = *env;
	while (ft_strncmp(current->pref, "PWD", 3))
		current = current->next;
	dir = delete_slash(dir);
	dir = add_slash(dir);
	str = ft_strdup(current->string);
	free(current->string);
	dir = ft_strjoinfree(str, dir, true, true);
	current->string = dir;
	free(current->full_string);
	current->full_string = ft_strjoin("PWD=", dir);
}

static void	change_pwd(char *dir, t_env **env)
{
	t_env	*current;
	char	*buf;

	current = *env;
	buf = strdup(dir);
	while (ft_strncmp(current->pref, "PWD", 3))
	{
		current =  current->next;
		if (current == NULL)
		{
			create_pwd(env);
			return ;
		}
	}
	if (!ft_strncmp(dir, "..", 2))
		going_back(env);
	else if (ft_strncmp(dir, "/home", 5))
		small_change(buf, env);
	else if (!ft_strncmp(dir, "/home", 5))
		full_change(buf, env);
}

static char	*getoldpwd(t_env **env)
{
	t_env	*current;

	current = *env;
	while (ft_strncmp(current->pref, "PWD", 3))
	{
		current = current->next;
		if (current == NULL)
			return (NULL);
	}
	return (current->string);
}

void	mini_cd(char **str, t_env **env, t_data *data)
{
	char	*old;

	old = getoldpwd(env);
	if (chdir(str[1]) != 0)
	{
		error(ERR_FLAG, str[0], str[1], data);
		return ;
	}
	change_oldpwd(old, env);
	change_pwd(str[1], env);
}