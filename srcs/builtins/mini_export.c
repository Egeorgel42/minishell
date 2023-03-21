/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:03:25 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/15 16:00:24 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_input(char **str, t_data *data)
{
	int	i;

	i = 0;
	if (!str[1])
		return ;
	if (str[1][0] >= '0' && str[1][0] <= '9')
		error(ERR_EXP, str[0], str[1], data);
	while (str[1][i] && str[1][i] != '=')
	{
		if ((str[1][i] >= '0' && str[1][i] <= '9')
			|| (str[1][i] >= 'a' && str[1][i] <= 'z')
			|| (str[1][i] >= 'A' && str[1][i] <= 'Z') || str[1][i] == '_')
			i++;
		else
			error(ERR_EXP, str[0], str[1], data);
	}
}

void	mini_export(char **str, t_data *data)
{
	t_env	*current;
	t_env	*buf;


	current = data->env;
	check_input(str, data);
	while (current->next->next != NULL)
		current = current->next;
	buf = create_node(str[1]);
	buf->next = current->next;
	current->next = buf;
	return ;
}
