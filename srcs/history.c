/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:17:01 by egeorgel          #+#    #+#             */
/*   Updated: 2023/05/02 19:03:14 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_history_line(t_data *data)
{
	char	*buf;
	char	*line;

	line = get_next_line(data->history_fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			buf = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			buf = ft_strdup(line);
		if (buf)
		{
			add_history(buf);
			free(data->last_history);
			data->last_history = ft_strdup(buf);
			free(buf);
			free(line);
		}
		line = get_next_line(data->history_fd);
	}
}

void	get_history(t_data *data)
{
	char	*home;

	home = get_str_env(data, "HOME");
	if (!home)
	{
		error(ERR_HOME_HIS, NULL, NULL, data);
		data->history_fd = -1;
		return ;
	}
	home = ft_strjoinfree(home, "/minishell_history", true, false);
	data->history_fd = open(home, O_CREAT | O_RDWR | O_APPEND, 000644);
	free(home);
	if (data->history_fd == -1)
	{
		error(ERR_MAX, NULL, NULL, data);
		return ;
	}
	get_history_line(data);
}

void	save_history(t_data *data)
{
	char	*line;

	if (!ft_strcmp(data->last_history, data->prompt))
		add_history(data->prompt);
	if (data->history_fd != -1 && !ft_strcmp(data->last_history, data->prompt))
	{
		line = ft_strjoin(data->prompt, "\n");
		ft_putstr_fd(line, data->history_fd);
		free(line);
	}
	free(data->last_history);
	data->last_history = ft_strdup(data->prompt);
}
