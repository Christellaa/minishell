/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:28:40 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/12 15:28:14 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_assignment(char *word)
{
	int		i;
	char	*equal_pos;
	int		in_quote;

	in_quote = 0;
	i = 0;
	equal_pos = ft_strchr(word, '=');
	if (!equal_pos)
		return (-1);
	while ((word + i) <= equal_pos)
	{
		if (word[i] == SINGLE_QUOTE || word[i] == DOUBLE_QUOTE)
			in_quote = !in_quote;
		if (in_quote)
			return (-1);
		i++;
	}
	return (ASSIGNMENT);
}

int	is_word(char *word)
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
	int		single_quote;
	int		double_quote;
	char	*word;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == SINGLE_QUOTE && !double_quote)
			single_quote = !single_quote;
		else if (input[i] == DOUBLE_QUOTE && !single_quote)
			double_quote = !double_quote;
		else if (ft_isspace(input[i]) && !single_quote && !double_quote)
			break ;
		i++;
	}
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
