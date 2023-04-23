/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:15:00 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/04/23 15:15:44 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env *copy_env_list(t_env *head) 
{
	t_env *new_head = NULL;
    t_env *current = head;
    while (current != NULL) 
	{
        t_env *new_node = create_node(current->full_string);
        if (new_head == NULL) 
		{
            new_head = new_node;
        } 
		else 
		{
            t_env *last = new_head;
            while (last->next != NULL) 
			{
                last = last->next;
            }
            last->next = new_node;
        }
        current = current->next;
    }
    return (new_head);
}

void	swap(t_env *a, t_env *b)
{
	char	*prefix_a;
	char	*full_string_a;
	char	*prefix_b;
	char	*full_string_b;

	prefix_a = ft_strdup(a->pref);
	full_string_a = ft_strdup(a->full_string);
	prefix_b = ft_strdup(b->pref);
	full_string_b = ft_strdup(b->full_string);
	free(a->pref);
	free(a->full_string);
	a->pref = prefix_b;
	a->full_string = full_string_b;
	free(b->pref);
	free(b->full_string);
	b->pref = prefix_a;
	b->full_string = full_string_a;
}

void	sort_and_print(t_env *head)
{
	t_env	*current;
	t_env	*cnext;
	t_env	*fprint;

	current = head;
	while (current != NULL)
	{
		cnext = current->next;
		while (cnext != NULL)
		{
			if (strcmp(current->pref, cnext->pref) > 0)
				swap(current, cnext);
			cnext = cnext->next;
		}
		current = current->next;
	}
	fprint = head;
	while (fprint != NULL)
	{
		printf("%s\n", fprint->full_string);
		fprint = fprint->next;
	}
}