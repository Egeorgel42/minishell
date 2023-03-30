/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:00:16 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/30 15:58:07 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_input(char **str, t_data *data)
{
	int	i;

	i = 0;
	if (!str[1] || str[2])
	{
		data->cmd_status = 2;
		error(ERR_ARGS, str[0], NULL, data);
		return (false);
	}
	if (str[1][0] >= '0' && str[1][0] <= '9')
	{
		error(ERR_EXP, str[0], str[1], data);
		return (false);
	}
	while (str[1][i])
	{
		if ((str[1][i] >= '0' && str[1][i] <= '9')
			|| (str[1][i] >= 'a' && str[1][i] <= 'z')
			|| (str[1][i] >= 'A' && str[1][i] <= 'Z') || str[1][i] == '_')
			i++;
		else
		{
			error(ERR_EXP, str[0], str[1], data);
			return (false);
		}
	}
	return (true);
}

void	mini_unset(t_data *data, char **str)
{
	t_env	*env;
	t_env	*prev;

	if (!check_input(str, data))
		return ;
	env = get_in_env(data, str[1]);
	prev = get_prev_in_env(data, str[1]);
	if (!env)
		return ;
	prev->next = env->next;
	free(env->full_string);
	free(env->pref);
	free(env->string);
	free(env);
}
