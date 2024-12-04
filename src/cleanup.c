/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:01:56 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/04 15:17:48 by cde-sous         ###   ########.fr       */
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

int	cleanup(t_data *data)
{
	if (data)
	{
		if (data->env_list)
			free_keyval(data->env_list);
		free(data);
	}
	exit(EXIT_SUCCESS);
}