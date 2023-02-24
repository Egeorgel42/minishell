/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:34:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/24 01:26:59 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_startincharset(char *str, char *charset)
{
	int	i;
	int	j;

	i = 0;
	if (!charset)
		return (str);
	if (!str)
		return (NULL);
	while (str[i])
	{
		j = -1;
		while (charset[++j])
			if (str[i] == charset[j])
				return (str + i);
		i++;
	}
	return (NULL);
}

void	ft_strrem(char *str, char *rem)
{
	int		i;
	int		j;
	int		x;
	bool	removed;

	i = 0;
	x = -1;
	removed = false;
	if (ft_strcmp(str, rem))
	{
		free(str);
		str = NULL;
		return ;
	}
	while (str[i])
	{
		j = 0;
		while (rem[j] && rem[j] == str[i + j] && !removed)
			j++;
		if (!rem[j] && !removed)
		{
			i += j;
			removed = true;
		}
		str[++x] = str[i++];
	}
	str[++x] = '\0';
}

char	**sep_input(char *input)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 1;
	res = malloc(sizeof(char *) * 3);
	if (input[0] && input[0] == input[1])
	{
		res[0] = ft_substr(input, 0, 2);
		j++;
	}
	else
		res[0] = ft_substr(input, 0, 1);
	while (ft_strchr("\t\v\n\f\r ", input[j]))
		j++;
	i = j;
	while (input[i] && !ft_strchr("\t\n\v\f\r ><|", input[i]))
		i++;
	res[1] = ft_substr(input, j, i - j);
	res[2] = NULL;
	printf("%s||%s\n", res[0], res[1]);
	return (res);
}
