/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:39:05 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/31 17:10:12 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exit_status(t_data *data, char **str, int i)
{
	char	*status;

	status = ft_itoa(data->status);
	replace_in_str(str, status, i, i + 2);
	free(status);
	return (i);
}

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
	if ((*str)[i + 1] == '?' && !quotes[0])
		return (exit_status(data, str, i));
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
	if (j == i + 1 && !(((*str)[j] == '\'' && !quotes[1])
		|| ((*str)[j] == '"' && !quotes[0])))
		return (i);
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

static bool	developp_env(t_data *data, char **str)
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
		{
			error(ERR_HOME, NULL, NULL, data);
			return (false);
		}
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
	return (true);
}

bool	get_env(t_data *data)
{
	t_list	*buf;

	buf = data->lst;
	while (buf && !ft_strchr(buf->str, '|'))
	{
		if (!developp_env(data, &buf->str))
			return (false);
		buf = buf->next;
	}
	return (true);
}
