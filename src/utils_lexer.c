/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:28:23 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/07 11:29:41 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_assignment(char *word)
{
	int		i;
	char	*equal_pos;

	i = 0;
	equal_pos = ft_strchr(word, '=');
	if (!equal_pos)
		return (-1);
	while ((word + i) <= equal_pos)
	{
		if (word[i] == SINGLE_QUOTE || word[i] == DOUBLE_QUOTE)
			return (-1);
		i++;
	}
	return (ASSIGNMENT);
}

int	is_word(char *word)
{
	int	i;

	i = get_word_len(word, 2);
	if (i > 0)
		return (WORD);
	else
		return (-1);
}

int	is_chevron(char *word)
{
	if (word[0] == '<' && word[1] == '>')
		return (TRUNC);
	else if (word[0] == '<' && word[1] != '<')
		return (INFILE);
	else if (word[0] == '<' && word[1] == '<')
		return (HEREDOC);
	else if (word[0] == '>' && word[1] != '>')
		return (TRUNC);
	else if (word[0] == '>' && word[1] == '>')
		return (APPEND);
	return (-1);
}

int	get_token_type(char *word)
{
	int	type;

	type = is_assignment(word);
	if (type != -1)
		return (type);
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
		len = get_word_len(word, 2);
	return (len);
}
