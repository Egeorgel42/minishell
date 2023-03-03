/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:34:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/03 21:57:51 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_strrem(char *str, char *rem)
{
	int		i;
	int		j;
	int		x;
	bool	removed;

	i = 0;
	x = -1;
	removed = false;
	if (ft_strcmp(str, rem))
	{
		free(str);
		str = NULL;
		return ;
	}
	while (str[i])
	{
		j = 0;
		while (rem[j] && rem[j] == str[i + j] && !removed)
			j++;
		if (!rem[j] && !removed)
		{
			i += j;
			removed = true;
		}
		str[++x] = str[i++];
	}
	str[++x] = '\0';
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

void	free2lst(t_list **lst)
{
	free((*lst)->next);
	free(*lst);
	*lst = NULL;
}

void	remove_from_list(t_list **lst, t_list *rem)
{
	t_list	*buf;

	buf = *lst;
	if (!(*lst)->next)
		free(lst);
	else if (!(*lst)->next->next)
		free2lst(lst);
	else if (!rem->next)
		free(rem);
	else if (!rem->next->next)
		free2lst(&rem);
	else if (*lst == rem)
	{
		*lst = (*lst)->next->next;
		free2lst(&buf);
	}
	else
	{
		while (buf->next)
		{
			if (buf->next == rem)
			{
				buf->next = rem->next->next;
				free(rem->next);
				free(rem);
				break ;
			}
			buf = buf->next;
		}
	}
}
