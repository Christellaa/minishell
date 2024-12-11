/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:28:23 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/11 16:30:04 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_token_type(char *word)
{
	int	type;

	if (ft_strchr(word, '='))
		return (ASSIGNMENT);
	type = is_word(word);
	if (type != -1)
		return (type);
	type = is_chevron(word);
	if (type != -1)
		return (type);
	if (word[0] == '|')
		return (PIPE);
	return (-1);
}

int	get_word_len(char *word)
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
		else if (ft_isspace(word[i]) && !single_quote & !double_quote)
			break ;
		else if ((word[i] == '<' || word[i] == '>' || word[i] == '|')
			&& !single_quote && !double_quote)
			break ;
		i++;
	}
	return (i);
}

int	get_type_len(char *word, int type)
{
	int	len;

	len = 0;
	if (type == INFILE || type == TRUNC || type == PIPE)
	{
		len = 1;
		if (type == TRUNC && word[1] == '>')
			len = 2;
	}
	else if (type == HEREDOC || type == APPEND)
		len = 2;
	else if (type == WORD || type == ASSIGNMENT)
		len = get_word_len(word);
	return (len);
}
