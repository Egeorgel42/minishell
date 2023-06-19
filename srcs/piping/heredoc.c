/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:51:04 by egeorgel          #+#    #+#             */
/*   Updated: 2023/06/19 05:12:21 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_sig	g_sig;

static void	stop_all(t_data *data)
{
	t_pidlst	*pidlst;

	pidlst = data->pidlst;
	while (pidlst)
	{
		kill(pidlst->pid, SIGSTOP);
		pidlst = pidlst->next;
	}
}

static void	resume_all(t_data *data)
{
	t_pidlst	*pidlst;

	pidlst = data->pidlst;
	while (pidlst)
	{
		kill(pidlst->pid, SIGCONT);
		pidlst = pidlst->next;
	}
}

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
	dup2(fd[1], STDOUT_FILENO);
	printf("%s", str);
	dup2(STDOUT_FILENO, STDOUT_FILENO);
	close(fd[1]);
	free(str);
	exit(0);
}

static bool	here_parent(t_data *data, int *fd)
{
	int		status;

	close(fd[1]);
	waitpid(g_sig.pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGTERM)
	{
		kill_all(data);
		close(fd[0]);
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
	data->act.__sigaction_u.__sa_handler = sigint_here;
	sigaction(SIGINT, &data->act, NULL);
	g_sig.heredoc = true;
	stop_all(data);
	if (data->in_fd != 0)
		close(data->in_fd);
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
	resume_all(data);
	signal(SIGQUIT, SIG_DFL);
	data->act.__sigaction_u.__sa_handler = sigint;
	sigaction(SIGINT, &data->act, NULL);
	g_sig.heredoc = false;
	return (true);
}
