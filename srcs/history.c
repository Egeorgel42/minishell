/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:17:01 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/23 18:58:58 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_history(t_data *data)
{
	char	*line;
	char	*home;

	home = get_home(data);
	if (!home)
		error(ERR_HOME_HIS, NULL, NULL, data);
	home = ft_strjoinfree(home, "/minishell_history", true, false);
	data->history_fd = open(home, O_CREAT | O_RDWR | O_APPEND, 000644);
	free(home);
	if (data->history_fd == -1)
		error(ERR_MAX, NULL, NULL, data);
	line = get_next_line(data->history_fd);
	while (line)
	{
		add_history(line);
		free(line);
		line = get_next_line(data->history_fd);
	}
}

void	save_history(t_data *data)
{
	char	*line;
	if (data->history_fd != -1)
	{
		line = ft_strjoin(data->prompt, "\n");
		ft_putstr_fd(line, data->history_fd);
		free(line);
	}
}