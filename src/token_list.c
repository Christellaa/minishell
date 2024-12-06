/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:46 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/06 16:48:16 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_token_type(char *word)
{
	int	type;

	if (ft_strchr(word, '='))
		return (ASSIGNMENT);
	if (check_forbidden_input(word))
		return (FORBIDDEN);
	type = is_word(word);
	if (type != -1)
		return (type);
	type = is_chevron(word);
	if (type != -1)
		return (type);
	if (word[0] == '|' && word[1] != '|' && word[2] != '|') // a revoir
		return (PIPE);
	return (-1);
}

int	get_type_len(char *word, int type)
{
	int	len;

	len = 0;
	if (type == INFILE || type == TRUNC)
	{
		if (type == TRUNC && word[1] == '>')
			len = 2;
		len = 1;
	}
	else if (type == HEREDOC || type == APPEND || type == PIPE)
		len = 2;
	else
		len = ft_strlen(word);
	return (len);
}

t_token	*create_token(int type, char *value, int len)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strndup(value, len);
	if (!value)
		return (NULL);
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token *last;

	if (!tokens || !new_token)
		return ;
	if (*tokens)
	{
		last = (*tokens);
		while (last->next)
			last = last->next;
		last->next = new_token;
		new_token->next = NULL;
	}
	else
	{
		new_token->next = NULL;
		*tokens = new_token;
	}
}