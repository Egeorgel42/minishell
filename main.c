/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:01:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/04 16:38:56 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inbuilts(t_data *data, t_list *lst)
{
	if (ft_strcmp(lst->str, "pwd"))
		mini_pwd(lst->str);
	else if (ft_strcmp(lst->str, "env"))
		mini_env(lst->str, data->env);
	else if (ft_strcmp(lst->str, "echo"))
		mini_echo(lst->str);
	else if (ft_strcmp(lst->str, "export"))
		mini_export(lst->str, data->env);
	else if (ft_strcmp(lst->str, "unset"))
		mini_unset(lst->str, data->env);
	else
		exec(); //future execve fonction call
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
//errno = 0 because readline sets errno to 2 for some reason