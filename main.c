/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:01:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/02 22:38:37 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_default(t_data *data, char **envp)
{
	data->envp = envp;
	data->prompt = "";
	data->in_fd = 1;
	data->out_fd = 1;
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
	data.lst = sep_token(data.prompt, &data);
	get_redirection_out(&data);
}
