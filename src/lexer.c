/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:28:40 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/07 11:29:36 by cde-sous         ###   ########.fr       */
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
	i = get_word_len(input, 1);
	word = ft_substr(input, 0, i);
	if (!word)
		return (NULL); // malloc error
	return (word);
}

void	lexer(t_data *data, char *input)
{
	int		i;
	char	*word;
	int		len;

	i = 0;
	if (!input)
		return ;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else
		{
			word = extract_word(&input[i]);
			if (!word)
				return ;
			len = tokenize(&data->token_list, word);
			free(word);
			i += len;
		}
	}
}
