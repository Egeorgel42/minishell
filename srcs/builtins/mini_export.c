/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:03:25 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/27 14:31:18 by egeorgel         ###   ########.fr       */
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
	return (true);
}

static void	export_in_env(t_data *data, t_env *current, char *str)
{
	char	*pref;
	t_env	*rem;
	t_env	*buf;
	t_env	*buf_rem;

	pref = find_pref(str);
	rem = get_prev_in_env(data, pref);
	if (rem)
	{
		buf_rem = rem->next->next;
		free(rem->next->full_string);
		free(rem->next->string);
		free(rem->next->pref);
		free(rem->next);
		rem->next = create_node(str);
		rem->next->next = buf_rem;
	}
	else
	{
		buf = create_node(str);
		buf->next = current->next;
		current->next = buf;
	}
	free(pref);
}

void	mini_export(char **str, t_data *data)
{
	t_env	*current;
	int		i;

	if (!str[1])
	{
		sort_and_print(copy_env_list(data->env));
		return ;
	}
	i = 1;
	current = data->env;
	while (current->next->next != NULL)
		current = current->next;
	while (str[i])
	{
		if (check_input(str[i], data))
			export_in_env(data, current, str[i]);
		i++;
	}
}
