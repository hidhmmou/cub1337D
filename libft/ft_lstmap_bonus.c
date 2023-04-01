/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 03:23:45 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/10/10 03:53:55 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_item;
	t_list	*item;

	new_item = NULL;
	while (lst && f)
	{
		item = ft_lstnew(f(lst->content));
		if (!item)
		{
			ft_lstclear(&new_item, del);
			return (NULL);
		}
		ft_lstadd_back(&new_item, item);
		lst = lst->next;
	}
	return (new_item);
}
