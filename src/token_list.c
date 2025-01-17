/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:46 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/17 15:27:23 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_token(int type, char *value, int len)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		print_error(6, NULL, NULL);
		return (free(value), NULL);
	}
	new_token->type = type;
	new_token->value = ft_strndup(value, len);
	if (!new_token->value)
	{
		print_error(6, NULL, NULL);
		return (free(new_token), NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token	*last;

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

int	create_and_add_token(t_token **cur_token, char *copy, char **split)
{
	int		i;
	t_token	*next;
	t_token	*last;
	t_token	*new_token;

	i = 0;
	next = (*cur_token)->next;
	last = *cur_token;
	while (split[++i])
	{
		new_token = create_token(ARG, split[i], ft_strlen(split[i]));
		if (!new_token)
			return (print_error(6, NULL, NULL), 0);
		last->next = new_token;
		last = new_token;
	}
	last->next = next;
	last->value = ft_strjoin_free_s1(last->value, copy, NULL);
	if (!last->value)
		return (print_error(6, NULL, NULL), 0);
	return (1);
}

int	split_token(char *expanded, t_token **cur_token, char *copy, char *tmp)
{
	char	**split;
	int		i;
	int		split_res;

	split = ft_split(expanded, ' ');
	if (!split)
		return (print_error(6, NULL, NULL), 0);
	free(expanded);
	(*cur_token)->value = ft_strjoin_free_both((*cur_token)->value, split[0]);
	if (!(*cur_token)->value)
		return (print_error(6, NULL, NULL), 0);
	split_res = create_and_add_token(cur_token, copy, split);
	i = 0;
	while (split[++i])
		free(split[i]);
	free(split);
	free(tmp);
	if (!split_res)
		return (0);
	return (1);
}
