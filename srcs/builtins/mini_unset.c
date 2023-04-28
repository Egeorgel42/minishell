/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:00:16 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/27 15:23:40 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_input(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "_"))
		return (false);
	if (str[0] >= '0' && str[0] <= '9')
	{
		error(ERR_EXP, str, str, data);
		return (false);
	}
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
			i++;
		else
		{
			error(ERR_EXP, str, str, data);
			return (false);
		}
	}
	if (str[i] == '=')
		return (false);
	return (true);
}

void	mini_unset(t_data *data, char **str)
{
	t_env	*env;
	t_env	*prev;
	int		i;

	i = 1;
	while (str[i])
	{
		if (check_input(str[i], data))
		{
			env = get_in_env(data, str[i]);
			prev = get_prev_in_env(data, str[i]);
			if (!env)
				return ;
			prev->next = env->next;
			free(env->full_string);
			free(env->pref);
			free(env->string);
			free(env);
			i++;
		}
		else
			i++;
	}
}
