/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:56:41 by egeorgel          #+#    #+#             */
/*   Updated: 2023/05/24 19:42:52 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_stat(t_data *data)
{
	struct stat	stats;

	data->cmd_status = 126;
	if (stat(data->lst->str, &stats))
	{
		if (errno == 2)
			data->cmd_status = 127;
		if (errno == 2 && !ft_strchr(data->lst->str, '/'))
			error_exit(ERR_CMD, data->lst->str, NULL, data);
		error_exit(ERRNO, data->lst->str, NULL, data);
	}
	if (S_ISDIR(stats.st_mode) && ft_strchr("./", data->lst->str[0]))
		error_exit(ERR_DIR, data->lst->str, NULL, data);
	else if (S_ISDIR(stats.st_mode))
		exit(1);
}

static void	access_err(t_data *data)
{
	errno = 0;
	check_stat(data);
	data->cmd_status = 126;
	if (data->lst->str[ft_strlen(data->lst->str) - 1] == '/')
		if (access(data->lst->str, F_OK) != 0)
			error_exit(ERR_NOT_DIR, data->lst->str, NULL, data);
	data->cmd_status = 127;
	error_exit(ERR_CMD, data->lst->str, NULL, data);
}

static char	*cur_dir(t_data *data)
{
	check_stat(data);
	if (access(data->lst->str, F_OK) == 0)
		return (ft_strdup(data->lst->str));
	errno = 0;
	data->cmd_status = 127;
	error_exit(ERR_FD, data->lst->str, NULL, data);
	return (NULL);
}

char	*access_p(t_data *data)
{
	char	*check_path;
	int		i;

	i = -1;
	errno = 0;
	if (*data->lst->str == '.')
		return (cur_dir(data));
	while (data->path[++i])
	{
		if (!data->path)
		{
			data->cmd_status = 127;
			error_exit(ERR_FD, data->lst->str, NULL, data);
		}
		check_path = ft_strjoinfree(data->path[i], "/", false, false);
		check_path = ft_strjoinfree(check_path, data->lst->str, true, false);
		if (access(check_path, F_OK) == 0)
			return (check_path);
		free(check_path);
	}
	access_err(data);
	return (NULL);
}
