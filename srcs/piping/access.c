/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:56:41 by egeorgel          #+#    #+#             */
/*   Updated: 2023/05/15 17:03:27 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	test_dirs(t_data *data)
{
	char	**str;
	char	*buf;
	int		i;

	str = ft_split(data->lst->str, '/');
	if (!str || !str[1])
		return ;
	i = 0;
	buf = ft_strdup(str[0]);
	while (str[++i])
	{
		if (access(buf, R_OK) && str[i])
			error_exit(ERR_PERM, data->lst->str, NULL, data);
		buf = ft_strjoinfree(buf, "/", true, false);
		buf = ft_strjoinfree(buf, str[i], true, false);
	}
	ft_freetab((void **)str);
	free(buf);
}

static void	check_stat(t_data *data)
{
	struct stat	stats;

	data->cmd_status = 126;
	if (stat(data->lst->str, &stats))
		error_exit(ERRNO, data->lst->str, NULL, data);
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
	test_dirs(data);
	data->cmd_status = 127;
	if (ft_strchr(data->lst->str, '/'))
		error_exit(ERR_FD, data->lst->str, NULL, data);
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
	if (!data->path)
	{
		data->cmd_status = 127;
		error_exit(ERR_FD, data->lst->str, NULL, data);
	}
	while (data->path[++i])
	{
		check_path = ft_strjoinfree(data->path[i], "/", false, false);
		check_path = ft_strjoinfree(check_path, data->lst->str, true, false);
		if (access(check_path, F_OK) == 0)
			return (check_path);
		free(check_path);
	}
	access_err(data);
	return (NULL);
}
