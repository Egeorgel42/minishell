/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:03:25 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/14 22:24:00 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_export(char **str, t_env **env)
{
	t_env	*current;
	t_env	*buf;


	current = *env;
	while (current->next->next != NULL)
		current = current->next;
	buf = create_node(str[1]);
	buf->next = current->next;
	current->next = buf;
	return ;
}
