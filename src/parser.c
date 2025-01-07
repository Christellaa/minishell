/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:29 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/07 16:56:51 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_token_type(t_token **token_list)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = *token_list;
	while (tmp)
	{
		if (tmp->type == ASSIGNMENT)
		{
			if (*token_list != tmp)
			{
				prev = get_prev_token(*token_list, tmp);
				if (prev->type == CMD || prev->type == ARG)
					tmp->type = ARG;
			}
		}
		else if (tmp->type == WORD)
		{
			if (*token_list != tmp)
				replace_word_type(token_list, &tmp);
			else
				tmp->type = CMD;
		}
		tmp = tmp->next;
	}
}

int	is_order_valid(t_token *list, t_token *current, t_token *next)
{
	if (current->type == ASSIGNMENT || current->type == FILENAME)
		return (1);
	else if (current->type == INFILE || current->type == HEREDOC
		|| current->type == TRUNC || current->type == APPEND)
		return (next && next->type == FILENAME);
	else if (current->type == PIPE)
	{
		if (current != list)
			return (next && next->type != PIPE);
		return (0);
	}
	else if (current->type == CMD || current->type == ARG)
		return (!next || next->type != CMD);
	return (0);
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
	int	err;

	if (!data->token_list)
		return (-1); // empty token list, not an error
	err = is_valid_assignment(&data->token_list);
	if (err == -1)
		return (-1); // need a word before '='
	else if (err == -2)
		return (-1); // malloc fail
	if (are_quotes_closed(&data->token_list) == -1)
		return (-1); // ' or " not closed
	delete_empty_tokens(&data->token_list);
	if (!data->token_list)
		return (-1); // empty token list
	replace_token_type(&data->token_list);
	// check if order of pipeline is valid
	if (!validate_pipeline(data->token_list))
		return (-1); // invalid pipeline order
	return (0);
}

/*
TODO:
- rename functions
*/
