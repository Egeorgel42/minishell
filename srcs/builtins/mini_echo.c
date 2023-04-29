/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:43:30 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/29 20:37:11 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	str_echo(t_data *data, char **str, int flag, int i)
{
	char	*res;

	res = ft_strdup(str[i]);
	while (str[++i])
	{
		res = ft_strjoinfree(res, " ", true, false);
		res = ft_strjoinfree(res, str[i], true, false);
	}
	if (flag == 0)
		res = ft_strjoinfree(res, "\n", true, false);
	ft_putstr_fd(res, data->out_fd);
	free(res);
}

void	mini_echo(t_data *data, char **str)
{
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	if (!str[1])
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (ft_strcmp(str[1], "-n"))
	{
		flag = 1;
		i++;
	}
	if (!str[++i])
		return ;
	str_echo(data, str, flag, i);
}
