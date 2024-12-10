/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:01:56 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/10 13:18:33 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_keyval(t_keyval *pair)
{
	t_keyval	*tmp;

	while (pair)
	{
		tmp = pair;
		pair = pair->next;
		free(tmp->raw);
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

int	cleanup(t_data *data, int type)
{
	if (data)
	{
		if (type == 1) // cleanup de fin
		{
			if (data->token_list)
				free_tokens(data->token_list);
			if (data->env_list)
				free_keyval(data->env_list);
			free(data);
		}
		if (type == 0) // cleanup a chaque boucle
		{
			if (data->token_list)
				free_tokens(data->token_list);
			data->token_list = NULL;
		}
	}
	return (0);
}
