/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:29 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/28 11:28:35 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		validate_pipeline(t_token **token_list, t_data *data);
int		is_order_valid(t_token **list, t_token *current, t_token **next,
			t_data *data);
void	delete_token_chevron(t_token **list, t_token *current, t_token **next);

int	parse_input(t_data *data, char *input)
{
	if (!lex_input(input, data))
	{
		free(input);
		return (0);
	}
	free(input);
	replace_token_type(&data->token_list);
	if (!validate_pipeline(&data->token_list, data))
		return (0);
	if (!expand_tokens(data) || !data->token_list)
		return (0);
	data->exit_code = 0; // useful?
	return (1);
}

int	validate_pipeline(t_token **token_list, t_data *data)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = *token_list;
	while (current_token)
	{
		next_token = current_token->next;
		if (is_order_valid(token_list, current_token, &next_token, data))
			return (0);
		current_token = next_token;
	}
	return (1);
}

int	is_order_valid(t_token **list, t_token *current, t_token **next,
		t_data *data)
{
	if (current->type == PIPE)
	{
		if (current == *list || !*next || (*next && (*next)->type == PIPE))
			return (print_error(5, "|", NULL, data));
	}
	else if (current->type == INFILE || current->type == HEREDOC
		|| current->type == TRUNC || current->type == APPEND)
	{
		if (!*next)
			return (print_error(5, "newline", NULL, data));
		else if (*next && (*next)->type != FILENAME)
			return (print_error(5, (*next)->value, NULL, data));
		else
		{
			(*next)->type = current->type;
			delete_token_chevron(list, current, next);
		}
	}
	return (0);
}

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
