/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:01:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/06/19 05:07:00 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_sig	g_sig;

void	data_initialize(t_data *data, char **envp)
{
	data->prompt = NULL;
	data->print_path = true;
	data->pipe_fd = 0;
	data->in_fd = 0;
	data->out_fd = 1;
	data->status = 0;
	data->cmd_status = 0;
	data->last_history = ft_strdup("");
	get_errlst(data);
	data->envp = NULL;
	data->env = NULL;
	data->pidlst = NULL;
	data->get_status = true;
	start_pwd(data);
	create_env(envp, &data->env);
	get_path(data);
	update_envp(data);
	get_history(data);
	start_attr(data);
	start_env(data);
	g_sig.status = 0;
	sigaction(SIGINT, NULL, &data->act);
}

void	data_default(t_data *data)
{
	free(data->prompt);
	data->prompt = NULL;
	clear_pidlst(data);
	data->pidlst = NULL;
	data->pipe_fd = 0;
	data->in_fd = 0;
	data->out_fd = 1;
	data->cmd_status = 0;
	data->get_status = true;
	update_envp(data);
}

static void	minishell_loop_start(t_data *data)
{
	bool	quotes[2];

	data->act.__sigaction_u.__sa_handler = empty_sigint;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &data->act, NULL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->attr);
	data->prompt = readline("minishell> ");
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->saved);
	signal(SIGQUIT, sigquit);
	data->act.__sigaction_u.__sa_handler = sigint;
	if (data->prompt == NULL)
	{
		printf("exit\n");
		exit(data->status);
	}
	if (g_sig.status != 0)
		data->status = g_sig.status;
	g_sig.status = 0;
	errno = 0;
	quotes[0] = false;
	quotes[1] = false;
	data->lst = sep_token(data->prompt, data, quotes);
}

void	minishell_loop(t_data *data)
{
	minishell_loop_start(data);
	if (!data->lst)
	{
		free(data->prompt);
		return ;
	}
	save_history(data);
	if (!is_pipe(data))
		parent_cmd(data);
	else
	{
		while (data->lst)
			callstructure(data);
		wait_pids(data);
	}
	data_default(data);
}
//errno = 0 because readline sets errno to 2 for some reason

int	main(int argc, char **argv, char **envp)
{
	t_data			data;

	if (argc != -1)
		argv[0][0] = '0';
	data_initialize(&data, envp);
	while (1)
		minishell_loop(&data);
	close(data.history_fd);
}
