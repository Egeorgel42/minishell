/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:09:30 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/05/22 15:46:26 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_sig	g_sig;

long	exit_parsing(t_data *data, char **str)
{
	int	i;

	i = -1;
	while (str[1][++i])
	{
		data->cmd_status = 2;
		if (!ft_isdigit(str[1][i]))
			error_exit(ERR_ARGS, str[0], str[1], data);
	}
	i = ft_atoi(str[1]);
	return (i);
}

void	mini_exit(t_data *data, char **str)
{
	long	nbr;

	if (!str[1])
		exit(data->status);
	else if (str[2])
	{
		error(ERR_ARGS_NBR, str[0], NULL, data);
		return ;
	}
	nbr = exit_parsing(data, str);
	exit(nbr);
}
