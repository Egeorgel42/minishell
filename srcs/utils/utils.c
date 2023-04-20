/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:34:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/20 12:40:43 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	set_to_opposite(bool b)
{
	if (b)
		return (false);
	return (true);
}

char	*ft_startincharset(char *str, char *charset)
{
	int	i;
	int	j;

	i = 0;
	if (!charset)
		return (str);
	if (!str)
		return (NULL);
	while (str[i])
	{
		j = -1;
		while (charset[++j])
			if (str[i] == charset[j])
				return (str + i);
		i++;
	}
	return (NULL);
}

void	ft_rem_double_space(char *str, char *sep)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		while (str[i + 1] && ft_strchr(sep, str[i + 1])
			&& ft_strchr(sep, str[i]))
		{
			j = -1;
			while (str[i + ++j + 1])
				str[i + j] = str[i + j + 1];
			str[i + j] = '\0';
		}
	}
}

void	remove_from_list(t_list **lst, t_list *rem)
{
	t_list	*buf;

	buf = *lst;
	if (!(*lst)->next)
	{
		ft_lstdelone(*lst, free);
		*lst = NULL;
	}
	else if (*lst == rem)
	{
		*lst = (*lst)->next;
		ft_lstdelone(buf, free);
	}
	else
	{
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
}

void	rem_until_rem(t_list **lst, t_list *rem)
{
	t_list	*buf;
	t_list	*del;

	buf = *lst;
	if (rem == ft_lstlast(*lst))
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
