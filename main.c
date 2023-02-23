/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:01:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/23 22:06:22 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_default(t_data *data, char **envp)
{
	data->envp = envp;
	data->in_fd = malloc(sizeof(int));
	data->in_fd[0] = -2;
	data->out_fd = malloc(sizeof(int));
	data->out_fd[0] = -2;
	data->prompt = "";
	get_errlst(data);
}

int	main(int argc, char **envp)
{
	t_data	data;

	argc = 0;
	data_default(&data, envp);
	while (!*data.prompt)
		prompt(&data);
	errno = 0;
	get_redirection_out(&data);
}
