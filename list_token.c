/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:17:25 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/02 16:31:47 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*create_token(int type, char *value)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_token_to_list(t_tokens **tokens, t_tokens *new)
{
	t_tokens	*last;

	if (!tokens || !new)
		return ;
	if (*tokens)
	{
		last = (*tokens);
		while (last->next)
			last = last->next;
		last->next = new;
		new->prev = last;
		new->next = NULL;
	}
	else
	{
		new->next = NULL;
		new->prev = NULL;
		*tokens = new;
	}
}
