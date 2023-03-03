/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:43:30 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/03 22:52:36 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_flag(char *str)
{
	if (str[5] == '-' && str[6] == 'n' && str[7] == ' ')
		return (1);
	else
		return (0);
}

void	mini_echo(char *str)
{
	int	flag;
	int	i;

	i = 5;
	flag = check_flag(str);
	if (flag == 0)
	{
		while (str[i] != '\0')
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
		ft_putchar_fd('\n', 1);
	}
	if (flag == 1)
	{
		i = 8;
		while (str[i] != '\0')
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
}
