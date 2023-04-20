/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:38:12 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/20 12:41:22 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_pid(pid_t pid, t_data *data)
{
	t_pidlst	*new_pid;
	t_pidlst	*buf;

	new_pid = malloc(sizeof(t_pidlst));
	new_pid->next = NULL;
	new_pid->pid = pid;
	buf = data->pidlst;
	if (!buf)
	{
		data->pidlst = new_pid;
		return ;
	}
	while (buf->next)
		buf = buf->next;
	buf->next = new_pid;
}

void	clear_pidlst(t_data *data)
{
	t_pidlst	*buf_pid;

	while (data->pidlst)
	{
		buf_pid = data->pidlst->next;
		free(data->pidlst);
		data->pidlst = buf_pid;
	}
}

bool	is_pipe(t_data *data)
{
	t_list	*buf;

	buf = data->lst;
	while (buf)
	{
		if (ft_strcmp(buf->str, "|"))
			return (true);
		buf = buf->next;
	}
	return (false);
}

void	replace_in_str(char **str, char *replace, int start, int end)
{
	char	*res;

	res = ft_strjoinfree(ft_substr((*str), 0, start), replace, true, false);
	res = ft_strjoinfree(res, ft_substr((*str), end, ft_strlen(*str) - end),
			true, true);
	free(*str);
	*str = res;
}

t_pidlst	*last_pid(t_data *data)
{
	t_pidlst	*buf_pid;

	buf_pid = data->pidlst;
	if (!buf_pid)
		return (NULL);
	while (buf_pid->next)
		buf_pid = buf_pid->next;
	return (buf_pid);
}
