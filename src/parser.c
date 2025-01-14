/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:29 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/13 14:39:09 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_order_valid(t_token *list, t_token *current, t_token *next)
{
	if (current->type == PIPE)
	{
		if (current == list)
			return (0);
		return (next && next->type != PIPE);
	}
	return (1);
}

int	validate_pipeline(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (!is_order_valid(token_list, current, current->next))
			return (0);
		current = current->next;
	}
	return (1);
}

int	parser(t_data *data)
{
	if (!data->token_list)
		return (-1); // empty token list, not an error; uselful??
	replace_token_type(&data->token_list);
	if (!validate_pipeline(data->token_list))
		return (-2); // invalid pipeline order
	return (0);
}
