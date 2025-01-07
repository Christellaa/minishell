/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:56:41 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/07 16:29:56 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	are_quotes_closed(t_token **token_list)
{
	t_token	*tmp;
	char	*value;
	int		i;

	tmp = *token_list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == ASSIGNMENT)
		{
			value = tmp->value;
			i = get_word_len(value, 0);
			if (i == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	is_valid_assignment(t_token **token_list)
{
	t_token	*tmp;
	char	*equal_pos;
	char	*key;
	char	*value;

	tmp = *token_list;
	while (tmp)
	{
		if (tmp->type == ASSIGNMENT)
		{
			equal_pos = ft_strchr(tmp->value, '=');
			key = ft_substr(tmp->value, 0, equal_pos - tmp->value);
			if (!*key)
				return (free(key), -1);
			value = get_value(equal_pos);
			if (!value)
				return (free(key), -2);
			tmp = replace_assignment_token(token_list, tmp, key, value);
			free(key);
			free(value);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
