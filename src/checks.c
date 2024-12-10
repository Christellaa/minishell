/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:56:41 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/10 17:02:50 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_assignment(t_token *token)
{
	t_token	*tmp;
	char	*equal_pos;
	char	*key;
	char	*value;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == ASSIGNMENT)
		{
			// check if before = there's a value
			equal_pos = ft_strchr(tmp->value, '=');
			if (!equal_pos)
				return (NULL);
			key = ft_substr(token->value, 0, equal_pos - token->value);
			if (!key)
				return (NULL);
			if (*(equal_pos + 1) != '\0')
				value = ft_strdup(equal_pos + 1);
			else
				value = ft_strdup("");
			/* // delete current token
			free(token->value);
			// add 3 new tokens:
			// - key = assignment
			create_token(ASSIGNMENT, key, ft_strlen(key));
			// - equal_pos = assignment
			create_token(ASSIGNMENT, key, ft_strlen(equal_pos));
			// - value = assignment
			create_token(ASSIGNMENT, key, ft_strlen(value)); */
			free(key);
			free(value);
		}
		tmp = tmp->next;
	}
}

int	check_chevrons(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == INFILE || tmp->type == HEREDOC || tmp->type == TRUNC
			|| tmp->type == APPEND)
		{
			if (!tmp->next)
				return (-2);
			if (tmp->next->type == INFILE || tmp->next->type == HEREDOC
				|| tmp->next->type == TRUNC || tmp->next->type == APPEND)
				return (-1);
			if (tmp->next->type != WORD)
				return (-2);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_forbidden_input(char *word)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (word[i])
	{
		if (word[i] == SINGLE_QUOTE && !double_quote)
			single_quote = !single_quote;
		else if (word[i] == DOUBLE_QUOTE && !single_quote)
			double_quote = !double_quote;
		else if (ft_strchr(FORBIDDEN_CHARS, word[i]) && !single_quote
			&& !double_quote)
			return (1);
		else if (word[i] == '|' && word[i + 1] == '|' && !single_quote
			&& !double_quote)
			return (1);
		else if (word[i] == '?' && word[i + 1] != '$' && !single_quote
			&& !double_quote)
			return (1);
		i++;
	}
	return (0);
}
