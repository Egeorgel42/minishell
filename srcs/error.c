/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:16:37 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/15 15:57:34 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error(int err, char *input, char *token, t_data *data)
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
		if (token)
		{
			msg = ft_strjoinfree(msg, "'", true, false);
			msg = ft_strjoinfree(msg, token, true, false);
			msg = ft_strjoinfree(msg, "'", true, false);
		}
		msg = ft_strjoinfree(msg, "\n", true, false);
		ft_putstr_fd(msg, 2);
	}
	free(msg);
	exit(1);
}
/*
written like: "minishell: input: err_msg 'token'"
example: "minishell: cat_: command not found"
example: "minishell: empty argument after token '<'"
example: "minishell: pwd: Following option is invalid '-l'"
*/

void	get_errlst(t_data *data)
{
	data->errlst = malloc(sizeof(char *) * (ERR_MAX + 1));
	data->errlst[ERR_CMD] = strdup("Command not found");
	data->errlst[ERR_FD] = strdup("No such file or directory");
	data->errlst[ERR_PARSING] = strdup("Unexpected parsing error");
	data->errlst[ERR_UNSUPORTED] = strdup("Is not a valid input");
	data->errlst[ERR_QUOTES] = strdup("Unclosed quotes");
	data->errlst[ERR_EMPTY] = strdup("Empty argument after token");
	data->errlst[ERR_FLAG] = strdup("Following option is invalid");
	data->errlst[ERR_ARGS] = strdup("Invalid command arguments");
	data->errlst[ERR_EXP] = strdup("not a valid indentifier");
	data->errlst[ERR_MAX] = NULL;
}
