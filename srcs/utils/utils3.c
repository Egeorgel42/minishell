/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:38:51 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/06/10 18:42:02 by egeorgel         ###   ########.fr       */
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

bool	empty_pipe(t_list *lst, t_data *data)
{
	if (lst && lst == data->lst)
	{
		rem_until_rem(&data->lst, lst);
		if (data->in_fd != 0)
			close(data->in_fd);
		data->in_fd = data->pipe_fd;
		if (data->out_fd != 1)
			close(data->out_fd);
		return (true);
	}
	return (false);
}
