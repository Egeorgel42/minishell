/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:43:30 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/14 22:46:31 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_echo(char **str, t_data *data)
{
	char	*res;
	int		flag;
	int		i;

	res = NULL;
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
	else if (is_flaged(str))
		error(ERR_FLAG, str[0], str[1], data);
	if (!str[++i])
		return ;
	res = ft_strdup(str[i]);
	while (str[++i])
	{
		res = ft_strjoinfree(res, " ", true, false);
		res = ft_strjoinfree(res, str[i], true, false);
	}
	if (flag == 0)
		res = ft_strjoinfree(res, "\n", true, false);
	ft_putstr_fd(res, 1);
	free(res);
}
