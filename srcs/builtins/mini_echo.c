/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:43:30 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/06/19 05:10:34 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	str_echo(t_data *data, char **str, bool flag, int i)
{
	char	*res;

	res = ft_strdup(str[i]);
	while (str[++i])
	{
		res = ft_strjoinfree(res, " ", true, false);
		res = ft_strjoinfree(res, str[i], true, false);
	}
	if (!flag)
		res = ft_strjoinfree(res, "\n", true, false);
	dup2(data->out_fd, STDOUT_FILENO);
	printf("%s\n", res);
	dup2(STDOUT_FILENO, STDOUT_FILENO);
	free(res);
}

static int	is_flag(char **str, bool *flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[++i])
	{
		j = 0;
		if (*(str[i]) != '-')
			return (i);
		while (str[i][++j])
		{
			if (str[i][j] != 'n')
				return (i);
		}
		*flag = true;
	}
	return (i);
}

void	mini_echo(t_data *data, char **str)
{
	bool	flag;
	int		i;

	i = 0;
	flag = false;
	i = is_flag(str, &flag);
	if (!str[i] && flag)
		return ;
	else if (!str[i] && !flag)
	{
		dup2(data->out_fd, STDOUT_FILENO);
		printf("\n");
		dup2(STDOUT_FILENO, STDOUT_FILENO);
	}
	else
		str_echo(data, str, flag, i);
}
