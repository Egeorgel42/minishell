/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:20:08 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/27 14:28:41 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_string(char *str)
{
	int		len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (str[len])
		len++;
	return (ft_substr(str, len, (ft_strlen(str) + 1) - len));
}

char	*find_pref(char *str)
{
	int		len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return (ft_substr(str, 0, len));
}

t_env	*create_node(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->next = NULL;
	node->string = find_string(str);
	node->pref = find_pref(str);
	node->full_string = ft_strdup(str);
	return (node);
}

void	create_env(char **envp, t_env **env)
{
	int		i;
	t_env	*new_node;
	t_env	*cursor;

	i = -1;
	while (envp[++i])
	{
		new_node = create_node(envp[i]);
		if (*env == NULL)
			*env = new_node;
		else
		{
			cursor = *env;
			while (cursor->next != NULL)
				cursor = cursor->next;
			cursor->next = new_node;
		}
	}
}
