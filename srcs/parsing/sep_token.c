/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:45:46 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/20 12:44:41 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_sep_token(t_list	*lst, t_data *data)
{
	if (ft_strcmp(lst->str, "\n") || ft_strcmp(lst->str, "\v"))
		return (true);
	if (ft_strcmp(lst->str, "\f") || ft_strcmp(lst->str, "\r"))
		return (true);
	if (ft_strcmp(lst->str, "<<") || ft_strcmp(lst->str, ">>"))
		return (true);
	if (ft_strcmp(lst->str, "<") || ft_strcmp(lst->str, ">"))
		return (true);
	if (ft_strcmp(lst->str, "|") || ft_strcmp(lst->str, "\t"))
		return (true);
	if (ft_strcmp(lst->str, "~"))
		return (true);
	error(ERR_UNSUPORTED, lst->str, NULL, data);
	return (false);
}

static int	get_seperator(char *str, t_data *data, t_list **buf, bool *quotes)
{
	int		i;
	int		j;

	i = 0;
	if (str[i] && ft_strchr(" \n\t\v\f\r", str[i]))
		i++;
	j = i;
	while (str[j] && ft_strchr("|<>&(){}[];*", str[j])
		&& (!quotes[0] && !quotes[1]))
	{
		if (str[j] == '\'' && !quotes[1])
			quotes[0] = set_to_opposite(quotes[0]);
		else if (str[j] == '"' && !quotes[0])
			quotes[1] = set_to_opposite(quotes[1]);
		j++;
	}
	if (i != j)
	{
		(*buf)->next = ft_lstnew(ft_substr(str, i, j - i));
		if (!check_sep_token((*buf)->next, data))
			return (-1);
	}
	if (str[j] && ft_strchr(" \n\t\v\f\r", str[j]))
		j++;
	return (j);
}

static int	get_token(char *str, t_data *data, t_list **buf, bool *quotes)
{
	int		i;
	int		j;

	i = get_seperator(str, data, buf, quotes);
	if (i == -1)
		return (INT_MIN);
	j = i;
	while (str[j])
	{
		if (str[j] == '\'' && !quotes[1])
			quotes[0] = set_to_opposite(quotes[0]);
		else if (str[j] == '"' && !quotes[0])
			quotes[1] = set_to_opposite(quotes[1]);
		else if (ft_strchr(" |<>&(){}[];*\n\t\v\f\r", str[j])
			&& (!quotes[0] && !quotes[1]))
			break ;
		j++;
	}
	if ((*buf)->next)
	{
		if (i == j)
		{
			error(ERR_EMPTY, NULL, (*buf)->next->str, data);
			return (INT_MIN);
		}
		(*buf)->next->next = ft_lstnew(ft_substr(str, i, j - i));
	}
	else if (i != j)
		(*buf)->next = ft_lstnew(ft_substr(str, i, j - i));
	return (j);
}

t_list	*sep_token(char *str, t_data *data)
{
	int		i;
	bool	quotes[2];
	t_list	*lst;
	t_list	*buf;

	quotes[0] = false;
	quotes[1] = false;
	if (!str || !*str)
		return (NULL);
	ft_rem_double_space(str, " \n\t\v\f\r");
	lst = ft_lstnew(ft_strdup(""));
	buf = lst;
	i = 0;
	while (str[i])
	{
		i += get_token(str + i, data, &buf, quotes);
		if (i < 0)
		{
			ft_lstclear(&lst, free);
			save_history(data);
			return (NULL);
		}
		buf = ft_lstlast(buf);
	}
	if (quotes[0] || quotes[1])
	{
		error(ERR_QUOTES, NULL, NULL, data);
		save_history(data);
		ft_lstclear(&lst, free);
		return (NULL);
	}
	buf = lst->next;
	ft_lstdelone(lst, free);
	return (buf);
}
