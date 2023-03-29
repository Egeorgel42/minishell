/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:09:30 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/29 15:07:08 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_parsing(t_data *data, char **str)
{
	int	i;

	i = -1;
	if (ft_strlen(str[1]) > 3)
	{
		error(ERR_ARGS, str[0], str[1], data);
		return (-1);
	}
	while (str[1][++i])
	{
		if (!ft_isdigit(str[1][i]))
		{
			error(ERR_ARGS, str[0], str[1], data);
			return (-1);
		}
	}
	i = ft_atoi(str[1]);
	if (i < 0 || i > 255)
	{
		error(ERR_ARGS, str[0], str[1], data);
		return (-1);
	}
	return (i);
}

void	mini_exit(t_data *data, char **str)
{
	int	nbr;

	if (!str[1])
		exit(data->status);
	if (is_flaged(str))
		error(ERR_FLAG, str[0], str[1], data);
	else if (str[2])
		error(ERR_ARGS, str[0], str[1], data);
	nbr = exit_parsing(data, str);
	if (nbr < 0)
		return ;
	exit(nbr);
}
