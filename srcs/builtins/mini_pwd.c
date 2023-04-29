/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:09:43 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/29 20:39:55 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_pwd(char **str, t_data *data)
{
	char	*buffer;

	if (is_flaged(str))
	{
		data->cmd_status = 2;
		error(ERR_FLAG, str[0], str[1], data);
		return ;
	}
	buffer = getcwd(NULL, 0);
	if (!buffer)
		buffer = ft_strdup(data->pwd);
	ft_putstr_fd(buffer, data->out_fd);
	ft_putchar_fd('\n', data->out_fd);
	free(buffer);
}
