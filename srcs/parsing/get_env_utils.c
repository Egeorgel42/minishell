/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:26:10 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/28 20:56:08 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_status(t_data *data, char **str, int i)
{
	char	*status;

	status = ft_itoa(data->status);
	replace_in_str(str, status, i, i + 2);
	free(status);
	return (i);
}

void	parse_env(char **env_str, int i, bool *quotes)
{
	char	*buf;

	if (quotes[0] || quotes[1])
		return ;
	ft_rem_double_space(*env_str, " \n\t\v\f\r");
	if (i == 0 && ft_strchr(" \n\t\v\f\r", **env_str))
	{
		buf = ft_substr(*env_str, 1, ft_strlen(*env_str) - 1);
		free(*env_str);
		*env_str = buf;
	}
	replace_charset_to_c(*env_str, "\n\t\v\f\r", ' ');
}
