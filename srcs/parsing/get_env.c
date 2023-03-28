/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:39:05 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/28 00:09:26 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_env(char **env_str, int i, bool *quotes)
{
	char	*buf;

	if (quotes[0] || quotes[1])
		return ;
	ft_rem_double_space(*env_str, " \n\t\v\f\r");
	if (i == 0 && ft_strchr(" \n\t\v\f\r", **env_str))
	{
		buf = ft_substr(*env_str, 1, ft_strlen(*env_str) - 1);
		free(*env_str);
		*env_str = buf;
	}
	replace_charset_to_c(*env_str, "\n\t\v\f\r", ' ');
}

static int	find_env(t_data *data, char **str, int i, bool *quotes)
{
	char	*env;
	char	*env_str;
	int		j;

	j = i;
	while ((*str)[++j])
	{
		if ((*str)[j] == '\'' && !quotes[1])
			break ;
		else if ((*str)[j] == '"' && !quotes[0])
			break ;
		else if ((*str)[j] == '$' && !quotes[0])
			break ;
		else if (!(((*str)[j] >= '0' && (*str)[j] <= '9')
			|| ((*str)[j] >= 'a' && (*str)[j] <= 'z')
			|| ((*str)[j] >= 'A' && (*str)[j] <= 'Z') || (*str)[j] == '_'))
			break ;
	}
	env = ft_substr(*str, i + 1, j - i);
	env_str = get_str_env(data, env);
	if (!env_str)
		env_str = ft_strdup("");
	parse_env(&env_str, i, quotes);
	replace_in_str(str, env_str, i, j);
	j = i + ft_strlen(env_str) - 1;
	free(env_str);
	free(env);
	return (j);
}

static void	developp_env(t_data *data, char **str)
{
	int		i;
	bool	quotes[2];
	char	*buf;

	i = -1;
	quotes[0] = false;
	quotes[1] = false;
	if ((*str)[0] == '~' && (!(*str)[1] || (*str)[1] == '/'))
	{
		buf = get_str_env(data, "HOME");
		if (!buf)
			error(ERR_HOME, NULL, NULL, data);
		replace_in_str(str, buf, 0, 1);
		free (buf);
	}
	while ((*str)[++i])
	{
		if ((*str)[i] == '\'' && !quotes[1])
			quotes[0] = set_to_opposite(quotes[0]);
		else if ((*str)[i] == '"' && !quotes[0])
			quotes[1] = set_to_opposite(quotes[1]);
		else if ((*str)[i] == '$' && !quotes[0])
			i = find_env(data, str, i, quotes);
	}
}

void	get_env(t_data *data)
{
	t_list	*buf;

	buf = data->lst;
	while (buf && !ft_strchr(buf->str, '|'))
	{
		developp_env(data, &buf->str);
		buf = buf->next;
	}
}
