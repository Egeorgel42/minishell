/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:09:43 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/08 18:30:44 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_pwd(char **str, t_data *data)
{
	char	*buffer;

	if (is_flaged(str))
		error(ERR_FLAG, str[0], str[1], data);
	buffer = getcwd(NULL, 0);
	ft_putstr_fd(buffer, 1);
	free(buffer);
}
