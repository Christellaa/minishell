/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmin_max_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:11:00 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/27 14:16:35 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstmin_max_int(t_list *lst, int *min, int *max)
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	*min = *(int *)tmp->content;
	*max = *(int *)tmp->content;
	tmp = tmp->next;
	while (tmp)
	{
		if (*(int *)tmp->content < *min)
			*min = *(int *)tmp->content;
		if (*(int *)tmp->content > *max)
			*max = *(int *)tmp->content;
		tmp = tmp->next;
	}
}
