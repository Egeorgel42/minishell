/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:51:04 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/28 18:42:34 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_sig	g_sig;

static void	here_child(t_data *data, int *fd, char *sep)
{
	char	*tmp;
	char	*str;

	close(fd[0]);
	tmp = NULL;
	str = NULL;
	while (!ft_strcmp(tmp, sep))
	{
		str = ft_strjoinfree(str, tmp, true, true);
		if (str)
			str = ft_strjoinfree(str, "\n", true, false);
		tmp = readline("heredoc> ");
		if (!tmp)
			break ;
	}
	if (tmp)
		free(tmp);
	developp_env(data, &str);
	ft_putstr_fd(str, fd[1]);
	free(str);
	close(fd[1]);
	exit(0);
}

static bool	here_parent(t_data *data, int *fd)
{
	int		status;

	close(fd[1]);
	if (data->in_fd != 0)
		close(data->in_fd);
	waitpid(g_sig.pid, &status, 0);
	if (!WIFEXITED(status) && WTERMSIG(status) == SIGTERM)
	{
		close (fd[0]);
		data->status = 1;
		return (false);
	}
	data->in_fd = fd[0];
	return (true);
}

bool	heredoc(t_data *data, char *sep)
{
	int		fd[2];

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_here);
	g_sig.heredoc = true;
	if (pipe(fd) == -1)
		error_exit(ERR_MAX, NULL, NULL, data);
	g_sig.pid = fork();
	if (g_sig.pid == -1)
		error_exit(ERR_MAX, NULL, NULL, data);
	else if (g_sig.pid == 0)
		here_child(data, fd, sep);
	else if (g_sig.pid > 0)
		if (!here_parent(data, fd))
			return (false);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, SIG_IGN);
	g_sig.heredoc = false;
	return (true);
}
