/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:12:14 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/03 22:52:45 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_env(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (str[len] != str[2])
	{
		if (str[len] != ' ')
		{
			printf("Unavaible arguments");
			exit(1);
		}
		else
			len--;
	}
}

void	mini_env(char *str, t_env **env)
{
	t_env	*current;

	check_env(str);
	current = *env;
	while (current != NULL)
	{
		printf("%s\n", current->full_string);
		current = current->next;
	}
}
