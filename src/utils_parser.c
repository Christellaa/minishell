/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:24:28 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/08 12:58:15 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_value_empty(char *value)
{
	int		i;
	char	quote_type;

	quote_type = value[0];
	i = -1;
	while (value[++i])
	{
		if (value[i] != SINGLE_QUOTE && value[i] != DOUBLE_QUOTE)
			break ;
		else if (value[i] != quote_type)
			break ;
	}
	if (value[i] == '\0')
		return (1);
	return (0);
}

void	delete_empty_tokens(t_token **token_list)
{
	t_token	*tmp;
	t_token	*next;
	t_token	*prev;

	tmp = *token_list;
	while (tmp)
	{
		next = tmp->next;
		if (is_value_empty(tmp->value) == 1 && tmp->type != ASSIGNMENT)
		{
			if (*token_list == tmp)
				*token_list = tmp->next;
			else
			{
				prev = get_prev_token(*token_list, tmp);
				prev->next = tmp->next;
			}
			free(tmp->value);
			free(tmp);
		}
		tmp = next;
	}
}

void	replace_word_type(t_token **list, t_token **tmp)
{
	t_token	*prev;

	prev = get_prev_token(*list, *tmp);
	if (prev->type == INFILE || prev->type == HEREDOC || prev->type == TRUNC
		|| prev->type == APPEND)
		(*tmp)->type = FILENAME;
	else if (prev->type == CMD || prev->type == ARG)
		(*tmp)->type = ARG;
	else
		(*tmp)->type = CMD;
}

void	replace_token_type(t_token **token_list)
{
	t_token *tmp;
	t_token *prev;

	tmp = *token_list;
	while (tmp)
	{
		if (tmp->type == ASSIGNMENT)
		{
			if (*token_list != tmp)
			{
				prev = get_prev_token(*token_list, tmp);
				if (prev->type == CMD || prev->type == ARG)
					tmp->type = ARG;
			}
		}
		else if (tmp->type == WORD)
		{
			if (*token_list != tmp)
				replace_word_type(token_list, &tmp);
			else
				tmp->type = CMD;
		}
		tmp = tmp->next;
	}
}
