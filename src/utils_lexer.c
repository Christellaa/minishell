/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:28:23 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/09 11:10:31 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_word(char *word)
{
	int	i;

	i = get_word_len(word, 1);
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
	else if (type == WORD)
		len = get_word_len(word, 1);
	return (len);
}
