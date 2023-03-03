/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:01:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/03 22:50:39 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inbuilts(char *str, t_env	**env)
{
	str = cutspaces(str);
	if (!ft_strncmp(str, "pwd", 3))
		mini_pwd(str);
	else if (!ft_strncmp(str, "env", 3))
		mini_env(str, env);
	else if (!ft_strncmp(str, "echo", 3))
		mini_echo(str);
	else if (!ft_strncmp(str, "export", 6))
		mini_export(str, env);
	else if (!ft_strncmp(str, "unset", 5))
		mini_unset(str, env);
	else
		printf("Unavaible command");
}

void	data_default(t_data *data, char **envp)
{
	data->prompt = "";
	data->in_fd = 1;
	data->out_fd = 1;
	get_errlst(data);
	data->env = NULL;
	create_list(envp, &data->env);
}

int	main(int argc, char **envp)
{
	t_data	data;

	argc = 0;
	data_default(&data, envp);
	while (!*data.prompt)
		prompt(&data);
	errno = 0;
	data.lst = sep_token(data.prompt, &data);
	get_redirection_out(&data);
}
