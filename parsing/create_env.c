/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:20:08 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/03 22:58:40 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_string(char *str)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	res = malloc(ft_strlen(str) - len);
	while (str[len] != '\0')
	{
		res[i] = str[len];
		i++;
		len++;
	}
	res[i + 1] = '\0';
	return (res);
}

static char	*find_pref(char *str)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	len = 0;
	while (str[len] != '=')
		len++;
	res = malloc(sizeof(char) * (len + 1));
	while (str[i] != '=')
	{
		res[i] = str[i];
		i++;
	}
	res[i + 1] = '\0';
	return (res);
}

static char	*full_string(char *str)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	len = ft_strlen(str);
	res = malloc(sizeof(char) * len);
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i + 1] = '\0';
	return (res);
}

static t_env	*create_node(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->next = NULL;
	node->string = find_string(str);
	node->pref = find_pref(str);
	node->full_string = full_string(str);
	return (node);
}

void	create_env(char **envp, t_env **env)
{
	t_env	*new_node;
	t_env	*cursor;

	while (*envp != NULL)
	{
		new_node = create_node(*envp);
		if (*env == NULL)
			*env = new_node;
		else
		{
			cursor = *env;
			while (cursor->next != NULL)
				cursor = cursor->next;
			cursor->next = new_node;
		}
		envp++;
	}
}
