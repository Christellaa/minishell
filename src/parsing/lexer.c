/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:28:40 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/30 13:39:32 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_word(char *input, t_data *data);
int		tokenize_word(char *word, t_data **data);

int	lex_input(char *input, t_data *data)
{
	int		total_len;
	char	*word;
	int		token_len;

	total_len = 0;
	if (!input)
		return (0);
	while (input[total_len])
	{
		if (ft_isspace(input[total_len]))
			total_len++;
		else
		{
			word = extract_word(&input[total_len], data);
			if (!word)
				return (0);
			token_len = tokenize_word(word, &data);
			if (token_len == -1)
				return (free(word), 0);
			total_len += token_len;
			free(word);
		}
	}
	return (1);
}

char	*extract_word(char *input, t_data *data)
{
	int		len;
	char	*word;

	len = 0;
	if (!input)
		return (NULL);
	len = get_word_len(input);
	if (len == -1)
		return (print_error(6, NULL, data), NULL);
	word = ft_substr(input, 0, len);
	if (!word)
		return (print_error(0, NULL, data), NULL);
	return (word);
}

int	tokenize_word(char *word, t_data **data)
{
	t_token	**token_list;
	int		token_len;
	int		token_type;
	t_token	*new_token;

	token_list = &(*data)->token_list;
	token_type = get_token_type(word);
	token_len = get_token_type_len(word, token_type);
	new_token = NULL;
	new_token = create_token(token_type, word, token_len);
	add_token_to_list(token_list, new_token);
	if (!token_list || !new_token)
		return (print_error(0, NULL, *data), -1);
	return (token_len);
}
