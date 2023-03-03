/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:00:16 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/03 23:55:52 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*make_pref(char *str)
{
	int		i;
	char	*res;
	int		n;

	n = 0;
	i = 6;
	res = malloc(sizeof(char) * ft_strlen(str) - i);
	while (str[i] != '\0')
	{
		res[n] = str[i];
		i++;
		n++;
	}
	return (res);
}

static int	check_unset(char *str)
{
	if (ft_strlen(str) <= 6)
		return (0);
	return (1);
}

void	mini_unset(char *str, t_env **env)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = *env;
	if (!check_unset(str))
		return ;
	str = make_pref(str);
	while (current != NULL)
	{
		if (!ft_strncmp(current->full_string, str, ft_strlen(current->pref)))
		{
			if (prev != NULL)
				prev->next = current -> next;
			else
				*env = current -> next;
			free(current);
			return ;
		}
		prev = current;
		current = current -> next;
	}
	return ;
}
