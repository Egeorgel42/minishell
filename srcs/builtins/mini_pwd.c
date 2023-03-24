/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:09:43 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/24 17:21:46 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_in_env(t_env **env)
{
	t_env	*current;
	char	*str;

	current = *env;
	while (ft_strncmp("PWD", current->pref, 3))
		current = current->next;
	str = current->string;
	return (str);
}

void	mini_pwd(char **str, t_data *data, t_env **env)
{
	char	*buffer;

	if (is_flaged(str))
	{
		error(ERR_FLAG, str[0], str[1], data);
		return ;
	}
	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		buffer = find_in_env(env);
		ft_putstr_fd(buffer, 1);
		ft_putchar_fd('\n', 1);
		return ;
	}
	ft_putstr_fd(buffer, 1);
	ft_putchar_fd('\n', 1);
	free(buffer);
}
