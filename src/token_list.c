/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:46 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/28 12:20:15 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		create_and_add_split_tokens(t_token **token, char *copy,
			char **split_expanded);

t_token	*get_prev_token(t_token *list, t_token *current)
{
	t_token	*prev;

	prev = list;
	while (prev && prev->next != current)
		prev = prev->next;
	return (prev);
}

t_token	*create_token(int type, char *value, int len)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (free(value), NULL);
	new_token->type = type;
	new_token->value = ft_strndup(value, len);
	if (!new_token->value)
		return (free(new_token), NULL);
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token **token_list, t_token *new_token)
{
	t_token	*last_token;

	if (!token_list || !new_token)
		return ;
	if (*token_list)
	{
		last_token = (*token_list);
		while (last_token->next)
			last_token = last_token->next;
		last_token->next = new_token;
		new_token->next = NULL;
	}
	else
	{
		new_token->next = NULL;
		*token_list = new_token;
	}
}

int	split_token(char *expanded, t_token **token, char *copy, char *tmp)
{
	char	**split_expanded;
	int		i;
	int		split_res;

	split_expanded = ft_split(expanded, ' ');
	if (!split_expanded)
		return (-1);
	free(expanded);
	(*token)->value = ft_strjoin_free_both((*token)->value, split_expanded[0]);
	if (!(*token)->value)
		return (-1);
	split_res = create_and_add_split_tokens(token, copy, split_expanded);
	i = 0;
	while (split_expanded[++i])
		free(split_expanded[i]);
	free(split_expanded);
	free(tmp);
	return (split_res);
}

int	create_and_add_split_tokens(t_token **token, char *copy,
		char **split_expanded)
{
	int		i;
	t_token	*next;
	t_token	*last;
	t_token	*new_token;

	i = 0;
	next = (*token)->next;
	last = *token;
	while (split_expanded[++i])
	{
		new_token = create_token(ARG, split_expanded[i],
				ft_strlen(split_expanded[i]));
		if (!new_token)
			return (-1);
		last->next = new_token;
		last = new_token;
	}
	last->next = next;
	last->value = ft_strjoin_free_s1(last->value, copy, NULL);
	if (!last->value)
		return (-1);
	return (0);
}
