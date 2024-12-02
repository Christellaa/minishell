/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:33:01 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:37:28 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Iterates through the list lst and applies f to the content of each node
** Returns nothing
*/

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
