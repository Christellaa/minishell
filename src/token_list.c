/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:46 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/09 09:54:22 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_token(int type, char *value, int len)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		printf("Malloc error\n");
		return (free(value), NULL);
	}
	new_token->type = type;
	new_token->value = ft_strndup(value, len);
	if (!new_token->value)
	{
		printf("Malloc error\n");
		return (free(new_token), NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!tokens || !new_token)
		return ;
	if (*tokens)
	{
		last = (*tokens);
		while (last->next)
			last = last->next;
		last->next = new_token;
		new_token->next = NULL;
	}
	else
	{
		new_token->next = NULL;
		*tokens = new_token;
	}
}
