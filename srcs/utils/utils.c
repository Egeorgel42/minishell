/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:34:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/28 23:44:52 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	set_to_opposite(bool b)
{
	if (b)
		return (false);
	return (true);
}

char	*ft_startincharset(char *str, char *charset)
{
	int	i;
	int	j;

	i = 0;
	if (!charset)
		return (str);
	if (!str)
		return (NULL);
	while (str[i])
	{
		j = -1;
		while (charset[++j])
			if (str[i] == charset[j])
				return (str + i);
		i++;
	}
	return (NULL);
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

void	remove_from_list(t_list **lst, t_list *rem)
{
	t_list	*buf;

	buf = *lst;
	if (!(*lst)->next)
	{
		ft_lstdelone(*lst, free);
		*lst = NULL;
	}
	else if (*lst == rem)
	{
		*lst = (*lst)->next;
		ft_lstdelone(buf, free);
	}
	else
	{
		while (buf->next)
		{
			if (buf->next == rem)
			{
				buf->next = rem->next;
				ft_lstdelone(rem, free);
				break ;
			}
			buf = buf->next;
		}
	}
}

void	rem_until_rem(t_list **lst, t_list *rem)
{
	t_list	*buf;
	t_list	*del;

	buf = *lst;
	if (rem == ft_lstlast(*lst))
		ft_lstclear(lst, free);
	else
	{
		while (buf && buf != rem)
		{
			del = buf;
			buf = buf->next;
			ft_lstdelone(del, free);
		}
		if (buf)
		{
			del = buf;
			buf = buf->next;
			ft_lstdelone(del, free);
			*lst = buf;
		}
		else
			*lst = NULL;
	}
}

int		env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
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

void	update_envp(t_data *data)
{
	t_env	*env;
	char	**up_env;
	int		i;

	env = data->env;
	up_env = malloc(sizeof(char *) * (env_size(env) + 1));
	i = -1;
	while (env)
	{
		up_env[++i] = ft_strdup(env->full_string);
		env = env->next;
	}
	up_env[++i] = NULL;
	if (data->envp)
		ft_freetab((void **)data->envp);
	data->envp = up_env;
	if (data->path)
		ft_freetab((void **)data->path);
	get_path(data);
}

char	**get_cmd(t_data *data)
{
	t_list	*buf;
	char	**cmd;
	int		i;

	buf = data->lst;
	i = 0;
	while (buf && !ft_strcmp(buf->str, "|"))
	{
		buf = buf->next;
		i++;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	buf = data->lst;
	while (buf && !ft_strcmp(buf->str, "|"))
	{
		cmd[i] = ft_strdup(buf->str);
		buf = buf->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

bool	is_flaged(char **str)
{
	if (!str[1])
		return (false);
	if (str[1][0] == '-')
		return (true);
	return (false);
}

void	add_pid(pid_t pid, t_data *data)
{
	t_pidlst	*new_pid;

	new_pid = malloc(sizeof(t_pidlst));
	new_pid->next = data->pidlst;
	new_pid->pid = pid;
	data->pidlst = new_pid;
}

pid_t	last_pid(t_data *data)
{
	t_pidlst	*buf_pid;

	buf_pid = data->pidlst;
	while (buf_pid->next)
		buf_pid = buf_pid->next;
	return (buf_pid->pid);
}

void	clear_pidlst(t_data *data)
{
	t_pidlst	*buf_pid;

	while (data->pidlst)
	{
		buf_pid = data->pidlst->next;
		free(data->pidlst);
		data->pidlst = buf_pid;
	}
}

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

t_env	*get_prev_in_env(t_data *data, char *env)
{
	t_env	*buf;

	buf = data->env;
	if (!buf)
		return (NULL);
	while (buf->next && !ft_strcmp(buf->next->pref, env))
		buf = buf->next;
	if (buf->next)
		return (buf);
	return (NULL);
}

t_env	*get_in_env(t_data *data, char *env)
{
	t_env	*buf;

	buf = data->env;
	while (buf && !ft_strcmp(buf->pref, env))
		buf = buf->next;
	if (buf)
		return (buf);
	return (NULL);
}

void	start_pwd(t_data *data)
{
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
		error_exit(ERR_START_PWD, NULL, NULL, data);
}

/*need upgrade*/
void	ft_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(1);
}
