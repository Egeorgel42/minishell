/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:34:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/06 20:51:22 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ft_lstdelone(lst, free);
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
	if (rem == ft_lstlast(lst))
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

void	update_envp(t_data *data)
{
	t_env	*env;
	char	**up_env;
	int		i;
	int		j;

	env = data->env;
	up_env = malloc(sizeof(char *) * (env_size(env) + 1));
	i = -1;
	j = -1;
	while (env)
	{
		up_env[++i] = malloc(ft_strlen(env->full_string) + 1);
		while (env->full_string[++j])
			up_env[i][j] = env->full_string[j];
		up_env[i][j] = '\0';
		env = env->next;
	}
	up_env[++i] == NULL;
	ft_freetab(data->envp);
	data->envp = up_env;
}

char	**get_cmd(t_data *data)
{
	t_list	*buf;
	char	**cmd;
	int		i;
	int		j;

	buf = data->lst;
	i = 0;
	while (buf && !ft_strcmp(buf->str, "|"))
	{
		buf = buf->next;
		i++;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	i = -1;
	j = -1;
	while (buf && !ft_strcmp(buf->str, "|"))
	{
		cmd[++i] = malloc(ft_strlen(buf->str) + 1);
		while (buf->str[++j])
			cmd[i][j] = buf->str[++j];
		cmd[i][j] = '\0';
		buf = buf->next;
	}
	cmd[++i] == NULL;
	return (cmd);
}

char	**get_path(char **envp)
{
	int		i;
	char	*str;
	char	**buf;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			str = ft_strrem(envp[i], "PATH=");
			buf = ft_split(str, ':');
			free (str);
			return (buf);
		}
	}
	return (NULL);
}
