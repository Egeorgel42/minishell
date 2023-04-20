/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:37:33 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/20 12:37:51 by vkuzmin          ###   ########.fr       */
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

char	*get_str_env(t_data *data, char *env)
{
	t_env	*buf;

	buf = data->env;
	while (buf && !ft_strcmp(buf->pref, env))
		buf = buf->next;
	if (buf)
		return (ft_strdup(buf->string));
	return (NULL);
}
