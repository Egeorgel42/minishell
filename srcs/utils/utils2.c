/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:38:12 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/21 20:01:20 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_pipe(t_data *data)
{
	t_list	*buf;

	buf = data->lst;
	while (buf)
	{
		if (ft_strcmp(buf->str, "|"))
			return (true);
		buf = buf->next;
	}
	return (false);
}

void	replace_in_str(char **str, char *replace, int start, int end)
{
	char	*res;

	res = ft_strjoinfree(ft_substr((*str), 0, start), replace, true, false);
	res = ft_strjoinfree(res, ft_substr((*str), end, ft_strlen(*str) - end),
			true, true);
	free(*str);
	*str = res;
}

void	start_pwd(t_data *data)
{
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
		error_exit(ERR_START_PWD, NULL, NULL, data);
}

void	get_path(t_data *data)
{
	t_env	*env;

	env = get_in_env(data, "PATH");
	if (!env)
		data->path = NULL;
	else
		data->path = ft_split(env->string, ':');
}
