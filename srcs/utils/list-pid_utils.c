/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list-pid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:34:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/06/10 18:51:43 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_from_list(t_list **lst, t_list *rem)
{
	t_list	*buf;

	buf = *lst;
	if (!(*lst)->next)
	{
		ft_lstdelone(*lst, free);
		*lst = NULL;
		return ;
	}
	if (*lst == rem)
	{
		*lst = (*lst)->next;
		ft_lstdelone(buf, free);
		return ;
	}
	while (buf->next)
	{
		if (buf->next == rem)
		{
			buf->next = rem->next;
			ft_lstdelone(rem, free);
			break ;
		}
		buf = buf->next;
	}
}

void	rem_until_rem(t_list **lst, t_list *rem)
{
	t_list	*buf;
	t_list	*del;

	buf = *lst;
	if (!rem || rem == ft_lstlast(*lst))
		ft_lstclear(lst, free);
	else
	{
		while (buf && buf != rem)
		{
			del = buf;
			buf = buf->next;
			ft_lstdelone(del, free);
		}
		if (buf)
		{
			del = buf;
			buf = buf->next;
			ft_lstdelone(del, free);
			*lst = buf;
		}
		else
			*lst = NULL;
	}
}

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
