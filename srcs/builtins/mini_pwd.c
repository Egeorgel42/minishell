/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:09:43 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/05/29 22:40:00 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_pwd(t_data *data)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
		buffer = ft_strdup(data->pwd);
	ft_putstr_fd(buffer, data->out_fd);
	ft_putchar_fd('\n', data->out_fd);
	free(buffer);
}
