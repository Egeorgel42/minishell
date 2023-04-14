/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:01:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/14 13:50:43 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*g_prompt;

void	minishell_loop(t_data *data)
{
	g_prompt = data->prompt;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	data->prompt = readline("-> ");
	g_prompt = data->prompt;
	errno = 0;
	data->lst = sep_token(data->prompt, data);
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
	t_data	data;

	if (argc != -1)
		argv[0][0] = '0';
	data_initialize(&data, envp);
	while (1)
		minishell_loop(&data);
	close(data.history_fd);
}
