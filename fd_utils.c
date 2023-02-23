/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:41:17 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/23 22:11:15 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*new_fd_tab(int new_fd)
{
	int	*new_tab;

	new_tab = malloc(sizeof(int) * 2);
	new_tab[0] = new_fd;
	new_tab[1] = -2;
	return (new_tab);
}

int	*realloc_fd(int new_fd, int	*fds)
{
	int	*new_tab;
	int	i;

	i = 0;
	while (fds[i] >= -1)
		i++;
	new_tab = malloc(sizeof(int) * (i + 2));
	i = -1;
	while (fds[++i] >= -1)
		new_tab[i] = fds[i];
	new_tab[i] = new_fd;
	new_tab[++i] = -2;
	free(fds);
	return (new_tab);
}

int	last_fd(int *fds)
{
	int	last;
	int	i;

	i = -1;
	last = -2;
	while (fds[++i] >= -1)
		last = fds[i];
	return (last);
}
