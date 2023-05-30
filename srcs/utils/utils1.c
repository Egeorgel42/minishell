/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:37:33 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/05/29 22:53:25 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_charset_to_c(char *str, char *charset, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(charset, str[i]))
			str[i] = c;
	}
}

static void	rm_character(char *str, int *i)
{
	int	j;

	j = (*i) - 1;
	while (str[++j])
		str[j] = str[j + 1];
	(*i)--;
}

void	remove_quotes(t_data *data)
{
	int		i;
	t_list	*buf;
	bool	quotes[2];

	quotes[0] = false;
	quotes[1] = false;
	buf = data->lst;
	while (buf)
	{
		i = -1;
		while (buf->str[++i])
		{
			if (buf->str[i] == '\'')
				quotes[0] = set_to_opposite(quotes[0]);
			else if (buf->str[i] == '"')
				quotes[1] = set_to_opposite(quotes[1]);
			if (buf->str[i] == '\'' && !quotes[1])
				rm_character(buf->str, &i);
			else if (buf->str[i] == '"' && !quotes[0])
				rm_character(buf->str, &i);
		}
		buf = buf->next;
	}
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

void	ft_rem_double_space_quotes(char *str, char *sep)
{
	int		i;
	int		j;
	bool	quotes[2];

	i = -1;
	quotes[0] = false;
	quotes[1] = false;
	while (str[++i])
	{
		if (str[i] == '\'' && !quotes[1])
			quotes[0] = set_to_opposite(quotes[0]);
		else if (str[i] == '"' && !quotes[0])
			quotes[1] = set_to_opposite(quotes[1]);
		while (str[i + 1] && ft_strchr(sep, str[i + 1])
			&& ft_strchr(sep, str[i]) && !quotes[0] && !quotes[1])
		{
			j = -1;
			while (str[i + ++j + 1])
				str[i + j] = str[i + j + 1];
			str[i + j] = '\0';
		}
	}
}
