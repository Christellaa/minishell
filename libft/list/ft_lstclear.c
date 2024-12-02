/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:04:55 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:37:24 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Del and frees the given node and every successor of it
** The pointer to the list must be set to NULL
** Returns nothing
*/

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	if (!lst || !(*lst) || !del)
		return ;
	while (current)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
}
