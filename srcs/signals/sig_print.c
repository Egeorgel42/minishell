/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:20:33 by egeorgel          #+#    #+#             */
/*   Updated: 2023/06/02 21:29:19 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_messages(t_data *data, int sig)
{
	data->status = 128 + sig;
	if (sig == SIGINT)
		ft_printf("\n");
	if (sig == SIGQUIT)
		ft_printf("Quit: 3\n");
}
