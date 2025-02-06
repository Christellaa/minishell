/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:24:28 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 16:19:32 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_tools.h"

int		is_token_value_empty(char *value);

void	delete_empty_tokens(t_token **token_list)
{
	t_token	*current_token;
	t_token	*next;
	t_token	*prev;

	current_token = *token_list;
	while (current_token)
	{
		next = current_token->next;
		if (is_token_value_empty(current_token->value))
		{
			if (*token_list == current_token)
				*token_list = current_token->next;
			else
			{
				prev = get_prev_token(*token_list, current_token);
				prev->next = current_token->next;
			}
			free(current_token->value);
			free(current_token);
		}
		current_token = next;
	}
}

int	is_token_value_empty(char *value)
{
	return (value[0] == '\0' || ((value[0] == SINGLE_QUOTE
				|| value[0] == DOUBLE_QUOTE) && value[1] == value[0]
			&& value[2] == '\0'));
}

void	replace_token_type(t_token **token_list)
{
	t_token	*current_token;
	t_token	*prev_token;

	current_token = *token_list;
	while (current_token)
	{
		if (current_token->type == WORD)
		{
			if (*token_list == current_token)
				current_token->type = ARG;
			else
			{
				prev_token = get_prev_token(*token_list, current_token);
				if (prev_token->type == INFILE || prev_token->type == HEREDOC
					|| prev_token->type == TRUNC || prev_token->type == APPEND)
					current_token->type = FILENAME;
				else
					current_token->type = ARG;
			}
		}
		current_token = current_token->next;
	}
}

int	var_name_len(char *value)
{
	int	len;

	len = 0;
	if (value[len] == '?')
		return (1);
	if (ft_isdigit(value[len]))
		return (1);
	while (value[len])
	{
		if (value[len] != '_' && !ft_isalnum(value[len]))
			break ;
		len++;
	}
	return (len);
}
