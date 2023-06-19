/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:09:30 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/06/19 05:05:26 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_error(t_data *data)
{
	error(ERR_EXIT, "exit", NULL, data);
	exit(255);
}

static long long	exit_atoi(t_data *data, char *str)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	if (ft_strcmp(str, "-9223372036854775808"))
		return (LLONG_MIN);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		if (res < 0)
			exit_error(data);
		res += str[i++] - '0';
		if (res < 0)
			exit_error(data);
	}
	return (res * sign);
}

static long	exit_parsing(t_data *data, char **str)
{
	int	i;

	i = -1;
	while (str[1][++i])
	{
		data->cmd_status = 2;
		if ((!ft_isdigit(str[1][i]) && str[1][i] != '-' && str[1][i] != '+')
			|| i > 20)
			exit_error(data);
	}
	i = exit_atoi(data, str[1]);
	return (i);
}

void	mini_exit(t_data *data, char **str, bool pipe)
{
	long	nbr;

	if (!pipe)
		printf("exit\n");
	if (!str[1])
		exit(data->status);
	nbr = exit_parsing(data, str);
	if (str[2])
	{
		data->cmd_status = 1;
		error(ERR_ARGS_NBR, "exit", NULL, data);
		return ;
	}
	exit(nbr);
}
