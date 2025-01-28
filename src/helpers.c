/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:16:12 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/28 10:09:16 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char *equal_pos)
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

t_token	*get_prev_token(t_token *list, t_token *current)
{
	t_token	*prev;

	prev = list;
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

int	get_word_len(char *word)
{
	int		len;
	char	quote;

	len = 0;
	quote = '\0';
	while (word[len])
	{
		quote = has_quote(quote, word[len]);
		if (quote == '\0' && ft_isspace(word[len]))
			break ;
		len++;
	}
	if (quote != '\0')
		return (-1);
	return (len);
}

int	stop_word_len_at_special_char(char *word, int len)
{
	int		new_len;
	char	quote;

	new_len = 0;
	quote = '\0';
	while (new_len < len)
	{
		quote = has_quote(quote, word[new_len]);
		if (quote == '\0' && (ft_isspace(word[new_len]) || word[new_len] == '<'
				|| word[new_len] == '>' || word[new_len] == '|'))
			break ;
		new_len++;
	}
	if (quote != '\0')
		return (-1);
	return (new_len);
}

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (s3);
}
