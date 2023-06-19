/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:09:43 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/06/19 23:38:29 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_pwd(t_data *data)
{
	char	*buffer;
	int		saved;

	saved = dup(1);
	buffer = getcwd(NULL, 0);
	if (!buffer)
		buffer = ft_strdup(data->pwd);
	dup2(data->out_fd, STDOUT_FILENO);
	printf("%s\n", buffer);
	dup2(saved, STDOUT_FILENO);
	free(buffer);
}
