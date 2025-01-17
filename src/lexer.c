/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:28:40 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/17 15:27:13 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokenize(t_token **tokens, char *word)
{
	int		len;
	int		type;
	t_token	*value;

	type = get_token_type(word);
	len = get_type_len(word, type);
	value = NULL;
	value = create_token(type, word, len);
	add_token_to_list(tokens, value);
	if (!tokens || !value)
		return (-1);
	return (len);
}

char	*extract_word(char *input)
{
	int		i;
	char	*word;

	i = 0;
	if (!input)
		return (NULL);
	i = get_word_len(input, 0);
	if (i == -1)
		return (print_error(5, NULL, NULL), NULL);
	word = ft_substr(input, 0, i);
	if (!word)
		return (print_error(6, NULL, NULL), NULL);
	return (word);
}

int	lexer(t_data *data, char *input)
{
	int		i;
	char	*word;
	int		len;

	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else
		{
			word = extract_word(&input[i]);
			if (!word)
				return (0);
			len = tokenize(&data->token_list, word);
			if (len == -1)
				return (free(word), 0);
			i += len;
			free(word);
		}
	}
	return (1);
}
