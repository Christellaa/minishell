/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:16:12 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/09 21:08:00 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(char *equal_pos)
{
	char	*value;

	if (*(equal_pos + 1) != '\0')
		value = ft_strdup(equal_pos + 1);
	else
		value = ft_strdup("");
	if (!value)
		return (NULL);
	return (value);
}

t_token	*get_prev_token(t_token *prev, t_token *current)
{
	while (prev && prev->next != current)
		prev = prev->next;
	return (prev);
}

char	has_quote(char quote, char current_char)
{
	if (current_char == SINGLE_QUOTE || current_char == DOUBLE_QUOTE)
	{
		if (quote == '\0')
			quote = current_char;
		else if (quote == current_char)
			quote = '\0';
	}
	return (quote);
}

int	get_word_len(char *word, int flag)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (word[i])
	{
		quote = has_quote(quote, word[i]);
		if (quote == '\0' && ft_isspace(word[i]))
			break ;
		else if (quote == '\0' && flag == 1 && (word[i] == '<' || word[i] == '>'
				|| word[i] == '|'))
			break ;
		i++;
	}
	if (quote != '\0')
		return (-1);
	return (i);
}

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (s3);
}
