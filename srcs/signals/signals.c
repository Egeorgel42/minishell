/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:46:54 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/06/06 19:03:24 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_sig	g_sig;

void	sigint_here(int sig)
{
	ft_printf("\n");
	if (sig == SIGINT)
		kill(g_sig.pid, SIGTERM);
	g_sig.heredoc = false;
}

void	empty_sigint(int sig)
{
	ft_printf("\n");
	g_sig.status = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (sig)
		return ;
}

void	sigint(int sig)
{
	if (sig)
		return ;
}

void	sigquit(int sig)
{
	if (sig)
		return ;
}
