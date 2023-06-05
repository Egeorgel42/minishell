/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:00:43 by egeorgel          #+#    #+#             */
/*   Updated: 2023/06/02 17:23:24 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	start_path(t_data *data)
{
	t_env	*buf;

	buf = get_in_env(data, "PATH");
	if (!buf)
	{
		if (!data->env)
		{
			data->env = create_node(
					"PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
			data->print_path = false;
			return ;
		}
		buf = data->env;
		while (buf->next)
			buf = buf->next;
		buf->next
			= create_node("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		data->print_path = false;
	}
}

static void	start_shlvl(t_data *data)
{
	t_env	*buf;
	int		i;

	buf = get_in_env(data, "SHLVL");
	if (!buf)
	{
		buf = data->env;
		while (buf->next)
			buf = buf->next;
		buf->next = create_node("SHLVL=1");
	}
	else
	{
		i = ft_atoi(buf->string);
		i++;
		free(buf->string);
		free(buf->full_string);
		buf->string = ft_itoa(i);
		buf->full_string = ft_strjoin("SHLVL=", buf->string);
		buf->is_equal = true;
	}
}

static void	start_oldpwd(t_data *data)
{
	t_env	*buf;

	buf = get_in_env(data, "OLDPWD");
	if (!buf)
	{
		buf = data->env;
		while (buf->next)
			buf = buf->next;
		buf->next = create_node("OLDPWD");
	}
	else
	{
		free(buf->string);
		free(buf->full_string);
		buf->string = ft_strdup("");
		buf->full_string = ft_strdup("OLDPWD");
		buf->is_equal = false;
	}
}

static void	starts_pwd(t_data *data)
{
	t_env	*buf;
	char	*str;

	buf = get_in_env(data, "PWD");
	if (!buf)
	{
		str = getcwd(NULL, 0);
		buf = data->env;
		while (buf->next)
			buf = buf->next;
		str = ft_strjoinfree("PWD=", str, false, true);
		buf->next = create_node(str);
		free(str);
	}
}

void	start_env(t_data *data)
{
	start_path(data);
	start_oldpwd(data);
	starts_pwd(data);
	start_shlvl(data);
}
