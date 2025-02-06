/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:28:23 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 12:58:07 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_tools.h"

int	get_token_type(char *word);
int	is_word(char *word);
int	is_chevron(char *word);

int	get_token_type(char *word)
{
	int	type;

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

int	is_word(char *word)
{
	int	word_len;

	word_len = get_word_len(word);
	word_len = stop_word_len_at_special_char(word, word_len);
	if (word_len > 0)
		return (WORD);
	else
		return (-1);
}

int	is_chevron(char *word)
{
	if (word[0] == '<' && word[1] == '>')
		return (APPEND);
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

int	get_token_type_len(char *word, int type)
{
	int	word_len;

	word_len = 0;
	if (type == INFILE || type == TRUNC || type == PIPE)
	{
		word_len = 1;
		if (type == TRUNC && word[1] == '>')
			word_len = 2;
	}
	else if (type == HEREDOC || type == APPEND)
		word_len = 2;
	else if (type == WORD)
	{
		word_len = get_word_len(word);
		word_len = stop_word_len_at_special_char(word, word_len);
	}
	return (word_len);
}
