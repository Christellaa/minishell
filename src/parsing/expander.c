/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:53:48 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/09 16:41:14 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_tools/parsing_tools.h"

t_token	*quotes_to_tokens(char *token_value, t_token *prev, t_data *data);
t_token	*process_token(char *value, int *i, t_token *prev);
void	expand_tokens(t_token *token_list, t_data *data);
void	expand_single_token(t_token *token, t_data *data);

int	expand_tokens_and_handle_quotes(t_data *data)
{
	t_token	*current_token;
	t_token	*prev_token;
	t_token	*token_list;

	current_token = data->token_list;
	prev_token = NULL;
	while (current_token)
	{
		token_list = quotes_to_tokens(current_token->value, prev_token, data);
		if (!prev_token || prev_token->type != HEREDOC)
			expand_tokens(token_list, data);
		if (current_token->value)
			free(current_token->value);
		current_token->value = combine_tokens(token_list);
		free_tokens(token_list);
		prev_token = current_token;
		current_token = current_token->next;
	}
	remove_empty_tokens(&data->token_list);
	return (1);
}

t_token	*quotes_to_tokens(char *token_value, t_token *prev, t_data *data)
{
	t_token	*token_list;
	t_token	*new_token;
	int		i;

	token_list = NULL;
	i = 0;
	while (token_value[i])
	{
		new_token = process_token(&(token_value[i]), &i, prev);
		if (!new_token)
			print_error(0, NULL, data);
		add_token_to_list(&token_list, new_token);
	}
	return (token_list);
}

t_token	*process_token(char *value, int *i, t_token *prev)
{
	t_token	*new_token;
	int		len;
	int		type;

	if (prev && (prev->type == INFILE || prev->type == HEREDOC
			|| prev->type == TRUNC || prev->type == APPEND))
		type = FILENAME;
	else
		type = ARG;
	if (value[0] == SINGLE_QUOTE || value[0] == DOUBLE_QUOTE)
	{
		len = get_quoted_len(value, value[0]);
		if (!len)
			new_token = create_token(type, "\0", len, value[0]);
		else
			new_token = create_token(type, &value[1], len, value[0]);
		*i += len + 2;
	}
	else
	{
		len = get_len_until_quote(value);
		new_token = create_token(type, value, len, '\0');
		*i += len;
	}
	return (new_token);
}

void	expand_tokens(t_token *token_list, t_data *data)
{
	while (token_list)
	{
		if (token_list->quote == '\0' || token_list->quote == DOUBLE_QUOTE)
			expand_single_token(token_list, data);
		token_list = token_list->next;
	}
}

void	expand_single_token(t_token *token, t_data *data)
{
	char	*dollar_pos;
	char	*current;
	char	*expanded;

	while (token->value)
	{
		dollar_pos = ft_strchr(token->value, '$');
		if (!dollar_pos)
			break ;
		if (!ft_strcmp(dollar_pos, "$"))
			break ;
		current = token->value;
		expanded = handle_var_expansion(token, dollar_pos, data);
		if (expanded && *expanded == '\0')
		{
			free(expanded);
			expanded = NULL;
		}
		token->value = expanded;
		free(current);
	}
}
