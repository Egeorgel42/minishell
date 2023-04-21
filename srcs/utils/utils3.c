/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:38:51 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/21 20:01:28 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**get_cmd(t_data *data)
{
	t_list	*buf;
	char	**cmd;
	int		i;

	buf = data->lst;
	i = 0;
	while (buf && !ft_strcmp(buf->str, "|"))
	{
		buf = buf->next;
		i++;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	buf = data->lst;
	while (buf && !ft_strcmp(buf->str, "|"))
	{
		cmd[i] = ft_strdup(buf->str);
		buf = buf->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

bool	is_flaged(char **str)
{
	if (!str[1])
		return (false);
	if (str[1][0] == '-')
		return (true);
	return (false);
}

bool	set_to_opposite(bool b)
{
	if (b)
		return (false);
	return (true);
}
