/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <vkuzmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:03:25 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/17 18:11:47 by vkuzmin          ###   ########.fr       */
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
	while (str[1][i] && str[1][i] != '=')
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

void	mini_export(char **str, t_data *data)
{
	t_env	*current;
	t_env	*buf;
	int		i;

	i = 1;
	current = data->env;
	if (!check_input(str, data))
		return ;
	while (current->next->next != NULL)
		current = current->next;
	while (str[i])
	{
		buf = create_node(str[i++]);
		buf->next = current->next;
		current->next = buf;
	}
	return ;
}
