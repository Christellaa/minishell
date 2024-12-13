/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:24:28 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/13 14:22:48 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(char *equal_pos)
{
	char	*value;

	if (*(equal_pos + 1) != '\0')
		value = ft_strdup(equal_pos + 1);
	else
		value = ft_strdup("");
	if (!value)
		return (NULL);
	return (value);
}

void	epur_token_value(t_token **token)
{
	char	*trimmed;

	trimmed = ft_strepur((*token)->value);
	free((*token)->value);
	if (!trimmed)
		return ;
	(*token)->value = ft_strdup(trimmed);
	free(trimmed);
	if (!(*token)->value)
		return ;
}

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

void	delete_empty_quotes(t_token **token_list)
{
	t_token	*tmp;
	t_token	*next;
	t_token	*prev;

	tmp = *token_list;
	while (tmp)
	{
		next = tmp->next;
		epur_token_value(&tmp);
		if (is_value_empty(tmp->value) == 1 && tmp->type != ASSIGNMENT)
		{
			if (*token_list == tmp)
				*token_list = tmp->next;
			else
			{
				prev = *token_list;
				while (prev && prev->next != tmp)
					prev = prev->next;
				prev->next = tmp->next;
			}
			free(tmp->value);
			free(tmp);
		}
		tmp = next;
	}
}

void	determine_token_type(t_token *prev, t_token **tmp)
{
	while (prev && prev->next != *tmp)
		prev = prev->next;
	if (prev->type == INFILE || prev->type == HEREDOC || prev->type == TRUNC
		|| prev->type == APPEND)
		(*tmp)->type = FILENAME;
	else if (prev->type == CMD || prev->type == ARG)
		(*tmp)->type = ARG;
	else
		(*tmp)->type = CMD;
}
