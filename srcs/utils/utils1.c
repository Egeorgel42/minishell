/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:37:33 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/21 20:00:44 by egeorgel         ###   ########.fr       */
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

void	rm_charset_in_str(char *str, char *charset)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(charset, str[i]))
		{
			j = i - 1;
			while (str[++j])
				str[j] = str[j + 1];
			i--;
		}
	}
}

void	remove_quotes(t_data *data)
{
	t_list	*buf;

	buf = data->lst;
	while (buf)
	{
		rm_charset_in_str(buf->str, "'\"");
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
