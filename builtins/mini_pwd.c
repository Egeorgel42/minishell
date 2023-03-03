/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:09:43 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/03 22:52:53 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pwd(char *str)
{
	if (str[3] != ' ' && str[3] != '\0')
		exit(1);
}

void	mini_pwd(char *str)
{
	char	*buffer;

	check_pwd(str);
	buffer = getcwd(NULL, 0);
	ft_putstr_fd(buffer, 1);
	free(buffer);
	return ;
}
