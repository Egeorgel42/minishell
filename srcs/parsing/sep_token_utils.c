/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:59:52 by egeorgel          #+#    #+#             */
/*   Updated: 2023/05/29 22:42:57 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_sep_token(t_list	*lst, t_data *data)
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
	data->status = 258;
	error(ERR_UNSUPORTED, lst->str, NULL, data);
	return (false);
}

int	token_end(char *str, bool *quotes, int j)
{
	while (str[j])
	{
		if (str[j] == '\'' && !quotes[1])
			quotes[0] = set_to_opposite(quotes[0]);
		else if (str[j] == '"' && !quotes[0])
			quotes[1] = set_to_opposite(quotes[1]);
		else if (ft_strchr(" |<>&(){}[];*\n\t\v\f\r", str[j])
			&& (!quotes[0] && !quotes[1]))
			return (j);
		j++;
	}
	return (j);
}

bool	invalid_token(t_data *data, t_list *lst, int i)
{
	if (i < 0)
	{
		ft_lstclear(&lst, free);
		save_history(data);
		return (false);
	}
	return (true);
}

bool	check_first_pipe(t_data *data, char *str, bool *quotes)
{
	int		i;
	char	*buf;

	i = 0;
	if (str[i] && ft_strchr(" \n\t\v\f\r", str[i]))
		i++;
	sep_loop(str, &i, quotes);
	if (i != 0 && str[i - 1] == '|')
	{
		data->status = 258;
		buf = ft_substr(str, i - 1, 1);
		error(ERR_EMPTY, NULL, buf, data);
		free(buf);
		return (false);
	}
	return (true);
}
