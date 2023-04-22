/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:59:52 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/22 19:01:34 by egeorgel         ###   ########.fr       */
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
