/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:43:49 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/10 01:37:02 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strcmp(char *str, char *cmp)
{
	int	i;

	i = 0;
	if (!str || !cmp)
		return (false);
	if (ft_strlen(str) != ft_strlen(cmp))
		return (false);
	while (str[i] && str[i] == cmp[i])
	{
		i++;
	}
	if (str[i] || cmp[i])
		return (false);
	return (true);
}
