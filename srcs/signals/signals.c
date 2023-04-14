/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:46:54 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/14 13:57:50 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	*g_prompt;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_fprintf(2, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
