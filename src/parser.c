/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:29 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/17 13:42:29 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_order_valid(t_token *list, t_token *current, t_token *next)
{
	if (current->type == PIPE)
	{
		if (current == list || !next || (next && next->type == PIPE))
			return (print_error(0, "|", NULL), 0);
	}
	else if (current->type == INFILE || current->type == HEREDOC
		|| current->type == TRUNC || current->type == APPEND)
	{
		if (!next)
			return (print_error(0, "newline", NULL), 0);
		else if (next && next->type != FILENAME)
			return (print_error(0, next->value, NULL), 0);
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

int	parser(t_data *data, char *input)
{
	if (!lexer(data, input))
	{
		free(input);
		return (0);
	}
	free(input);
	replace_token_type(&data->token_list);
	if (!validate_pipeline(data->token_list))
		return (0);
	if (!expander(data))
		return (0);
	return (1);
}
