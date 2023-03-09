/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:12:14 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/09 20:35:26 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_env(char **str, t_data *data)
{
	t_env	*current;

	current = data->env;
	if (is_flaged(str))
		error(ERR_FLAG, str[0], str[1], data);
	if (str[1])
		error(ERR_ARGS, str[0], NULL, data);
	while (current != NULL)
	{
		printf("%s\n", current->full_string);
		current = current->next;
	}
}
