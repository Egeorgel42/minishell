/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:00:06 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/08 18:14:20 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	str = ft_strdup(current->string);
	free(current->string);
	dir = ft_strjoin(str, dir);
	current->string = dir;
	free(current->full_string);
	current->full_string = ft_strjoin("PWD=", dir);
}

static void	change_pwd(char *dir, t_env **env)
{
	t_env	*current;

	current = *env;
	while (ft_strncmp(current->pref, "PWD", 3))
		current = current->next;
	if (ft_strncmp(dir, "/home", 5))
		small_change(dir, env);
	if (!ft_strncmp(dir, "/home", 5))
		full_change(dir, env);
}

void	mini_cd(char *str, t_env **env)
{
	char	*res;
	int		i;
	int		n;
	char	*old;

	old = getcwd(NULL, 0);
	i = 3;
	n = 0;
	res = malloc(sizeof(char) * ft_strlen(str) - 2);
	while (str[i] != '\0')
	{
		res[n] = str[i];
		i++;
		n++;
	}
	if (chdir(res) != 0)
	{
		printf("Error");
		return ;
	}
	change_oldpwd(old, env);
	change_pwd(res, env);
}