/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:46 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/07 22:09:22 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_tools.h"

t_token	*create_token(int type, char *value, int len, char quote)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (free(value), NULL);
	new_token->type = type;
	new_token->value = ft_strndup(value, len);
	if (!new_token->value)
		return (free(new_token), NULL);
	new_token->quote = quote;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token **token_list, t_token *new_token)
{
	t_token	*last_token;

	if (!token_list || !new_token)
		return ;
	if (*token_list)
	{
		last_token = (*token_list);
		while (last_token->next)
			last_token = last_token->next;
		last_token->next = new_token;
		new_token->next = NULL;
	}
	else
	{
		new_token->next = NULL;
		*token_list = new_token;
	}
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

char	*combine_tokens(t_token *token_list)
{
	char	*value;

	value = ft_strdup("");
	if (!value)
		return (NULL);
	while (token_list)
	{
		if (token_list->value)
		{
			value = ft_strjoin_free_s1(value, token_list->value);
			if (!value)
				return (NULL);
		}
		token_list = token_list->next;
	}
	return (value);
}

void	remove_empty_tokens(t_token **token_list)
{
	t_token	*token;
	t_token	*prev;
	t_token	*next;

	token = *token_list;
	prev = NULL;
	while (token)
	{
		next = token->next;
		if (!token->value || token->value[0] == '\0')
		{
			if (token == *token_list)
				*token_list = next;
			else
				prev->next = token->next;
			free(token->value);
			free(token);
		}
		else
			prev = token;
		token = next;
	}
}
