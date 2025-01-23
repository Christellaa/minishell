/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:29 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/23 11:11:34 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_token_chevron(t_token **list, t_token *current, t_token **next)
{
	t_token	*prev;

	if (current == *list)
		*list = *next;
	else
	{
		prev = get_prev_token(*list, current);
		prev->next = *next;
	}
	*next = (*next)->next;
	free(current->value);
	free(current);
}

int	is_order_valid(t_token **list, t_token *current, t_token **next)
{
	if (current->type == PIPE)
	{
		if (current == *list || !*next || (*next && (*next)->type == PIPE))
			return (print_error(0, "|", NULL));
	}
	else if (current->type == INFILE || current->type == HEREDOC
		|| current->type == TRUNC || current->type == APPEND)
	{
		if (!*next)
			return (print_error(0, "newline", NULL));
		else if (*next && (*next)->type != FILENAME)
			return (print_error(0, (*next)->value, NULL));
		else
		{
			(*next)->type = current->type;
			delete_token_chevron(list, current, next);
		}
	}
	return (0);
}

int	validate_pipeline(t_token **token_list, t_data *data)
{
	t_token	*current;
	t_token	*next;
	int		code;

	current = *token_list;
	while (current)
	{
		next = current->next;
		code = is_order_valid(token_list, current, &next);
		if (code != 0)
		{
			data->exit_code = code;
			return (0);
		}
		current = next;
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
	if (!validate_pipeline(&data->token_list, data))
		return (0);
	if (!expander(data) || !data->token_list)
		return (0);
	data->exit_code = 0;
	return (1);
}
