/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:59 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/17 14:37:12 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	can_split(t_token *token_list, t_token *cur_token, int to_split, char quote)
{
	t_token	*prev;
	t_token	*tmp;

	prev = token_list;
	tmp = cur_token;
	if (token_list != cur_token)
		prev = get_prev_token(token_list, tmp);
	if (to_split == 1 && quote == '\0' && prev->type != INFILE
		&& prev->type != TRUNC && prev->type != APPEND)
		return (1);
	return (0);
}

char	*join_str_without_external_quotes(char *value, char quote)
{
	char	*str;
	char	*new_value;

	new_value = ft_strdup("");
	if (!new_value)
		return (print_error(6, NULL, NULL), NULL);
	while (*value)
	{
		if ((*value == SINGLE_QUOTE || *value == DOUBLE_QUOTE) && quote == '\0')
			quote = *value;
		else if (quote != *value)
		{
			str = ft_char_to_str(*value);
			if (!str)
				return (print_error(6, NULL, NULL), NULL);
			new_value = ft_strjoin_free_both(new_value, str);
			if (!new_value)
				return (print_error(6, NULL, NULL), free(new_value), free(str),
					NULL);
		}
		else if (quote == *value)
			quote = '\0';
		value++;
	}
	return (new_value);
}

int	remove_external_quotes(t_token **token)
{
	char	quote;
	char	*value;
	char	*new_value;

	quote = '\0';
	value = (*token)->value;
	new_value = join_str_without_external_quotes(value, quote);
	if (!new_value)
		return (0);
	free((*token)->value);
	(*token)->value = new_value;
	return (1);
}
