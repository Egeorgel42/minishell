/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:01:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/27 18:01:11 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_sig	g_sig;

void	data_initialize(t_data *data, char **envp)
{
	data->prompt = NULL;
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
	start_pwd(data);
	create_env(envp, &data->env);
	get_path(data);
	update_envp(data);
	get_history(data);
	start_attr();
	g_sig.status = 0;
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
	update_envp(data);
}

static void	minishell_loop_start(t_data *data)
{
	g_sig.prompt = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_sig.attr);
	data->prompt = readline("minishell> ");
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_sig.saved);
	if (data->prompt == NULL)
	{
		ft_printf("exit\n");
		exit(data->status);
	}
	if (g_sig.status != 0)
		data->status = g_sig.status;
	g_sig.status = 0;
	g_sig.prompt = data->prompt;
	errno = 0;
	data->lst = sep_token(data->prompt, data);
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
	}
	wait_pids(data);
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
