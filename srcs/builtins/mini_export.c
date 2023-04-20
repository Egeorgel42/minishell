/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:03:25 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/20 12:45:28 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_input(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
	{
		error(ERR_EXP, str, str, data);
		return (false);
	}
	while (str[i] && str[i] != '=')
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
	if (str[i] != '=')
		return (false);
	return (true);
}

void	mini_export(char **str, t_data *data)
{
	t_env	*current;
	t_env	*buf;
	int		i;

	i = 1;
	current = data->env;
	while (current->next->next != NULL)
		current = current->next;
	while (str[i])
	{
		if (check_input(str[i], data))
		{
			buf = create_node(str[i]);
			buf->next = current->next;
			current->next = buf;
		}
		i++;
	}
	return ;
}
