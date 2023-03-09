/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:24:52 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/03 18:35:08 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*firstlst;
	t_list	*new;

	if (!lst || !del)
		return (NULL);
	firstlst = ft_lstnew(f(lst->str));
	new = firstlst;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew(f(lst->str));
		if (!(new->next))
		{
			ft_lstclear(&firstlst, del);
			return (0);
		}
		new = new->next;
		lst = lst->next;
	}
	return (firstlst);
}
