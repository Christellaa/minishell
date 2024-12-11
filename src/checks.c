/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:56:41 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/11 16:07:01 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes_close(t_token *token)
{
	int		single_quote;
	int		double_quote;
	char	*value;

	single_quote = 0;
	double_quote = 0;
	if (token->type == WORD)
	{
		value = token->value;
		while (*value)
		{
			if (*value == SINGLE_QUOTE)
				single_quote = !single_quote;
			if (*value == DOUBLE_QUOTE)
				double_quote = !double_quote;
			value++;
		}
		if (single_quote || double_quote)
			return (-1);
	}
	return (0);
}

int	check_assignment(t_token **token_list)
{
	t_token	*tmp;
	char	*equal_pos;
	char	*key;
	char	*value;

	tmp = *token_list;
	while (tmp)
	{
		if (tmp->type == ASSIGNMENT)
		{
			equal_pos = ft_strchr(tmp->value, '=');
			key = ft_substr(tmp->value, 0, equal_pos - tmp->value);
			if (!*key)
				return (free(key), -1);
			value = get_value(equal_pos);
			if (!value)
				return (free(key), -2);
			tmp = replace_assignment_token(token_list, tmp, key, value);
			free(key);
			free(value);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

int	check_chevrons(t_token *token)
{
	if (token->type == INFILE || token->type == HEREDOC || token->type == TRUNC
		|| token->type == APPEND)
	{
		if (!token->next)
			return (-2);
		if (token->next->type == INFILE || token->next->type == HEREDOC
			|| token->next->type == TRUNC || token->next->type == APPEND)
			return (-1);
		if (token->next->type != WORD)
			return (-2);
	}
	return (0);
}

int	check_forbidden_chars(t_token *token)
{
	int		single_quote;
	int		double_quote;
	char	*value;

	single_quote = 0;
	double_quote = 0;
	if (token->type == WORD)
	{
		value = token->value;
		while (*value)
		{
			if (*value == SINGLE_QUOTE)
				single_quote = !single_quote;
			if (*value == DOUBLE_QUOTE)
				double_quote = !double_quote;
			if (!single_quote && !double_quote)
				if (ft_strchr(FORBIDDEN_CHARS, *value) || (ft_strchr("?",
							*value) && ((value > token->value && *(value
									- 1) != '$') || value == token->value)))
					return (-1);
			value++;
		}
	}
	return (0);
}

int	check_double_pipe(t_token *token)
{
	if (token->type == PIPE)
		if (token->next)
			if (token->next->type == PIPE)
				return (-1);
	return (0);
}
