/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:17:01 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/28 17:14:18 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_history(t_data *data)
{
	char	*buf;
	char	*line;
	char	*home;

	home = get_str_env(data, "HOME");
	if (!home)
		error_exit(ERR_HOME_HIS, NULL, NULL, data);
	home = ft_strjoinfree(home, "/minishell_history", true, false);
	data->history_fd = open(home, O_CREAT | O_RDWR | O_APPEND, 000644);
	free(home);
	if (data->history_fd == -1)
		error_exit(ERR_MAX, NULL, NULL, data);
	line = get_next_line(data->history_fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			buf = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			buf = ft_strdup(line);
		add_history(buf);
		free(data->last_history);
		data->last_history = ft_strdup(buf);
		free(buf);
		free(line);
		line = get_next_line(data->history_fd);
	}
}

void	save_history(t_data *data)
{
	char	*line;

	if (data->history_fd != -1 && !ft_strcmp(data->last_history, data->prompt))
	{
		add_history(data->prompt);
		free(data->last_history);
		data->last_history = ft_strdup(data->prompt);
		line = ft_strjoin(data->prompt, "\n");
		ft_putstr_fd(line, data->history_fd);
		free(line);
	}
}
