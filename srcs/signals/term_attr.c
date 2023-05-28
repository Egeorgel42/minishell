/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_attr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:34:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/05/28 20:15:37 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_attr(t_data *data)
{
	tcgetattr(STDIN_FILENO, &data->saved);
	tcgetattr(STDIN_FILENO, &data->attr);
	data->attr.c_lflag &= ~(ICANON);
	data->attr.c_lflag &= ~(ECHOCTL);
}
