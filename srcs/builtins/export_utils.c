/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:15:00 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/29 20:38:25 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*copy_env_list(t_env *head)
{
	t_env	*new_head;
	t_env	*current;
	t_env	*last;
	t_env	*new_node;

	new_head = NULL;
	current = head;
	while (current)
	{
		new_node = create_node(current->full_string);
		if (!new_head)
			new_head = new_node;
		else
		{
			last = new_head;
			while (last->next)
			{
				last = last->next;
			}
			last->next = new_node;
		}
		current = current->next;
	}
	return (new_head);
}

static void	swap(t_env *a, t_env *b)
{
	char	*buf;

	buf = a->full_string;
	a->full_string = b->full_string;
	b->full_string = buf;
	buf = a->pref;
	a->pref = b->pref;
	b->pref = buf;
	buf = a->string;
	a->string = b->string;
	b->string = buf;
}

static int	strcmpp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] && !s2[i])
		return (1);
	if (!s1[i] && s2[i])
		return (-1);
	return (0);
}

static void	clear_env(t_env *env)
{
	t_env	*buf;

	while (env)
	{
		buf = env->next;
		free(env->full_string);
		free(env->pref);
		free(env->string);
		free(env);
		env = buf;
	}
}

void	sort_and_print(t_data *data, t_env *env)
{
	t_env	*next;
	t_env	*buf;

	buf = env;
	while (buf)
	{
		next = buf->next;
		while (next)
		{
			if (strcmpp(buf->pref, next->pref) > 0)
				swap(buf, next);
			next = next->next;
		}
		buf = buf->next;
	}
	buf = env;
	while (buf)
	{
		if (*buf->string && (!ft_strcmp(buf->pref, "PATH") || data->print_path))
			ft_fprintf(data->out_fd, "declare -x %s=\"%s\"\n",
				buf->pref, buf->string);
		else if ((!ft_strcmp(buf->pref, "PATH") || data->print_path))
			ft_fprintf(data->out_fd, "declare -x %s\n", buf->full_string);
		buf = buf->next;
	}
	clear_env(env);
}
