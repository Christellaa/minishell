/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:28:40 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/10 14:55:39 by carzhang         ###   ########.fr       */
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
	{
		printf("unclosed quote\n");
		return (NULL);
	}
	word = ft_substr(input, 0, i);
	if (!word)
		return (NULL); // malloc error
	return (word);
}

int	lexer(t_data *data, char *input)
{
	int		i;
	char	*word;

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
				return (-1);
			i += tokenize(&data->token_list, word);
			free(word);
		}
	}
	return (0);
}
