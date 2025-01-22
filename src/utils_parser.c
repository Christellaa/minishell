/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:24:28 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/22 15:03:07 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_value_empty(char *value)
{
	return (value[0] == '\0' || ((value[0] == SINGLE_QUOTE
				|| value[0] == DOUBLE_QUOTE) && value[1] == value[0]
			&& value[2] == '\0'));
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
		if (is_value_empty(tmp->value) == 1)
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

void	replace_token_type(t_token **token_list)
{
	t_token	*tmp;
	t_token	*prev;

	// if (!*token_list)
	// 	return ;
	tmp = *token_list;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (*token_list == tmp)
				tmp->type = ARG;
			else
			{
				prev = get_prev_token(*token_list, tmp);
				if (prev->type == INFILE || prev->type == HEREDOC
					|| prev->type == TRUNC || prev->type == APPEND)
					tmp->type = FILENAME;
				else
					tmp->type = ARG;
			}
		}
		tmp = tmp->next;
	}
}

int	var_name_len(char *value)
{
	int	len;

	len = 0;
	if (value[len] == '?')
		return (1);
	while (value[len])
	{
		if (ft_isspace(value[len]) || value[len] == SINGLE_QUOTE
			|| value[len] == DOUBLE_QUOTE || value[len] == '$')
			break ;
		len++;
	}
	return (len);
}
