/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 01:06:34 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/22 01:11:08 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmds(t_data *data)
{
	int		i;
	char	**str;

	i = -1;
	str = ft_split(data->prompt, ' ');
	while (str[++i])
	{
		if (ft_strcmp(str[i], "<<"))
	}
}
