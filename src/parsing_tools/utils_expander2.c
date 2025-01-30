/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:59 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/30 13:39:51 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_str_without_external_quotes(char *value, char quote);

int	can_split_token(t_token *token_list, t_token *token, int to_split,
		char quote)
{
	t_token	*prev;
	t_token	*current_token;

	prev = token_list;
	current_token = token;
	if (token_list != token)
		prev = get_prev_token(token_list, current_token);
	if (to_split == 1 && quote == '\0' && prev->type != INFILE
		&& prev->type != TRUNC && prev->type != APPEND)
		return (1);
	return (0);
}

int	remove_external_quotes(t_token **token, t_data *data)
{
	char	quote;
	char	*token_value;
	char	*new_value;

	quote = '\0';
	token_value = (*token)->value;
	new_value = join_str_without_external_quotes(token_value, quote);
	if (!new_value)
	{
		data->exit_code = print_error(0, NULL, data);
		return (0);
	}
	free((*token)->value);
	(*token)->value = new_value;
	return (1);
}

char	*join_str_without_external_quotes(char *value, char quote)
{
	char	*str;
	char	*new_value;

	new_value = ft_strdup("");
	if (!new_value)
		return (NULL);
	while (*value)
	{
		if ((*value == SINGLE_QUOTE || *value == DOUBLE_QUOTE) && quote == '\0')
			quote = *value;
		else if (quote != *value)
		{
			str = ft_char_to_str(*value);
			if (!str)
				return (NULL);
			new_value = ft_strjoin_free_both(new_value, str);
			if (!new_value)
				return (free(new_value), free(str), NULL);
		}
		else if (quote == *value)
			quote = '\0';
		value++;
	}
	return (new_value);
}
