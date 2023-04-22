/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:30:54 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/22 16:55:44 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_oldpwd(t_data *data, char **input)
{
	char	*buf;

	buf = get_str_env(data, "OLDPWD");
	if (!buf)
	{
		error(ERR_OLDPWD, input[0], NULL, data);
		return ;
	}
	cd_fction(data, buf);
	free(buf);
}
