/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_attr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:34:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/04/25 20:55:27 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_sig	g_sig;

void	start_attr(void)
{
	tcgetattr(STDIN_FILENO, &g_sig.saved);
	tcgetattr(STDIN_FILENO, &g_sig.attr);
	g_sig.attr.c_lflag &= ~(ICANON);
	g_sig.attr.c_lflag &= ~(ECHOCTL);
}
