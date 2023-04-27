/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:12:14 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/27 14:03:37 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_env(char **str, t_data *data)
{
	t_env	*current;

	current = data->env;
	if (is_flaged(str))
	{
		data->cmd_status = 2;
		error(ERR_FLAG, str[0], str[1], data);
		return ;
	}
	if (str[1])
	{
		data->cmd_status = 2;
		error(ERR_ARGS_NBR, str[0], NULL, data);
		return ;
	}
	while (current && *current->string)
	{
		printf("%s\n", current->full_string);
		current = current->next;
	}
}
