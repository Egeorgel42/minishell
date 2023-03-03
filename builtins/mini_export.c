/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:03:25 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/03 22:52:50 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_variable(char *str)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			counter++;
			if (str[i + 1] == ' ')
				counter--;
		}
		i++;
	}
	if (counter == 0)
		return (0);
	else
		return (1);
}

static char	*cutexport(char *str)
{
	int		i;
	char	*res;
	int		n;

	n = 0;
	i = 7;
	res = malloc(sizeof(char) * ft_strlen(str) - i);
	while (str[i] != '\0')
	{
		res[n] = str[i];
		i++;
		n++;
	}
	res[i + 1] = '\0';
	return (res);
}

void	mini_export(char *str, t_env **env)
{
	t_env	*current;

	current = *env;
	if (!check_variable(str))
		return ;
	str = cutexport(str);
	while (current->next != NULL)
		current = current->next;
	current -> next = create_node(str);
	return ;
}
