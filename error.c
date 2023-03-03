/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:16:37 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/02 21:38:13 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int err, char *input, t_data *data)
{
	char	*msg;

	if (input && *input)
		input = ft_strjoinfree(": ", input, false, true);
	msg = ft_strjoinfree("minishell", input, false, true);
	if (errno)
		perror(msg);
	else
	{
		msg = ft_strjoinfree(msg, ": ", true, false);
		msg = ft_strjoinfree(msg, data->errlst[err], true, false);
		msg = ft_strjoinfree(msg, "\n", true, false);
		ft_putstr_fd(msg, 2);
	}
	free(msg);
	exit(1);
}

void	get_errlst(t_data *data)
{
	data->errlst = malloc(sizeof(char *) * (ERR_MAX + 1));
	data->errlst[ERR_CMD] = strdup("command not found");
	data->errlst[ERR_FD] = strdup("No such file or directory");
	data->errlst[ERR_EMPTYREDIRECTION] = strdup("Empty file redirection");
	data->errlst[ERR_EXC] = strdup("Exceve error");
	data->errlst[ERR_PARSING] = strdup("Unexpected parsing error");
	data->errlst[ERR_UNSUPORTED] = strdup("Is not a valid input");
	data->errlst[ERR_QUOTES] = strdup("unclosed quotes");
	data->errlst[ERR_MAX] = NULL;
}
