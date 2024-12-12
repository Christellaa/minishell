/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:24:28 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/12 15:35:00 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(char *equal_pos)
{
	char	*value;
	char	*epur;

	if (*(equal_pos + 1) != '\0')
		value = ft_strdup(equal_pos + 1);
	else
		value = ft_strdup("");
	if (!value)
		return (NULL);
	epur = ft_strepur(value); // useful since i already trim all tokens' value?
	free(value);
	if (!epur)
		return (NULL);
	return (epur);
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

	tmp = *token_list;
	while (tmp)
	{
		next = tmp->next;
		epur_token_value(&tmp);
		if (is_value_empty(tmp->value) == 1)
		{
			if (tmp->type == ASSIGNMENT)
				continue ;
			else
				remove_token(token_list, tmp);
		}
		tmp = next;
	}
}
