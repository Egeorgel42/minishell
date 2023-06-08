/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:39:05 by egeorgel          #+#    #+#             */
/*   Updated: 2023/06/09 00:29:44 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	end_of_env(char *str, bool *quotes, int j)
{
	while (str[++j])
	{
		if (str[j] == '\'' && !quotes[1])
			return (j);
		else if (str[j] == '"' && !quotes[0])
			return (j);
		else if (str[j] == '$' && !quotes[0])
			return (j);
		else if (!((str[j] >= '0' && str[j] <= '9')
				|| (str[j] >= 'a' && str[j] <= 'z')
				|| (str[j] >= 'A' && str[j] <= 'Z') || str[j] == '_'))
			return (j);
	}
	return (j);
}

static int	find_env(t_data *data, char **str, int i, bool *quotes)
{
	char	*env;
	char	*env_str;
	int		j;

	j = i;
	if ((*str)[i + 1] == '?' && !quotes[0])
		return (exit_status(data, str, i));
	if (j == i + 1 && !(((*str)[j] == '\'' && !quotes[1])
		|| ((*str)[j] == '"' && !quotes[0])))
		return (i);
	j = end_of_env(*str, quotes, j);
	env = ft_substr(*str, i + 1, j - i - 1);
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

static void	env_loop(t_data *data, char **str, bool *quotes, int i)
{
	while ((*str)[++i])
	{
		if ((*str)[i] == '\'' && !quotes[1])
			quotes[0] = set_to_opposite(quotes[0]);
		else if ((*str)[i] == '"' && !quotes[0])
			quotes[1] = set_to_opposite(quotes[1]);
		else if ((*str)[i] == '$' && (*str)[i + 1] &&
			(*str)[i + 1] != '$' && !quotes[0])
			i = find_env(data, str, i, quotes);
	}
}

extern t_sig	g_sig;

bool	developp_env(t_data *data, char **str)
{
	int		i;
	bool	quotes[2];
	char	*buf;

	i = -1;
	quotes[0] = false;
	quotes[1] = false;
	if ((*str)[0] == '~' && (!(*str)[1] || (*str)[1] == '/') && !g_sig.heredoc)
	{
		buf = get_str_env(data, "HOME");
		if (!buf)
		{
			data->status = 1;
			error(ERR_HOME, NULL, NULL, data);
			data->cmd_status = 0;
			return (false);
		}
		replace_in_str(str, buf, 0, 1);
		free(buf);
	}
	env_loop(data, str, quotes, i);
	return (true);
}

bool	get_env(t_data *data)
{
	t_list	*buf;
	t_list	*nxt;

	buf = data->lst;
	while (buf && !ft_strchr(buf->str, '|'))
	{
		if (!developp_env(data, &buf->str))
			return (false);
		if (!*buf->str)
		{
			nxt = buf->next;
			remove_from_list(&data->lst, buf);
			buf = nxt;
		}
		else
			buf = buf->next;
	}
	return (true);
}
