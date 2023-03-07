/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:01:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/07 21:47:09 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_default(t_data *data, char **envp)
{
	data->prompt = "";
	data->in_fd = 1;
	data->out_fd = 1;
	get_errlst(data);
	data->envp = NULL;
	data->env = NULL;
	create_env(envp, &data->env);
	get_path(data);
	update_envp(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	argc = 0;
	argv[0][0] = '0';
	data_default(&data, envp);
	while (!*data.prompt)
		prompt(&data);
	errno = 0;
	data.lst = sep_token(data.prompt, &data);
	while (callstructure(&data))
	{
	}
	waitpid(data.pid, NULL, 0);
}
//errno = 0 because readline sets errno to 2 for some reason