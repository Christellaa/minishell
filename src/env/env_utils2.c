/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:17:40 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/09 19:18:12 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*create_env_node(char *raw, char *key, char *value, int is_exported)
{
	t_env	*new_env_pair;

	new_env_pair = malloc(sizeof(t_env));
	if (!new_env_pair)
		return (NULL);
	new_env_pair->raw = raw;
	new_env_pair->key = key;
	if (!value)
		new_env_pair->value = NULL;
	else
		new_env_pair->value = value;
	new_env_pair->is_exported = is_exported;
	new_env_pair->next = NULL;
	return (new_env_pair);
}

void	add_env_node_to_list(t_env **env_list, t_env *new_env_pair)
{
	t_env	*last_pair;

	if (!env_list || !new_env_pair)
		return ;
	if (*env_list)
	{
		last_pair = (*env_list);
		while (last_pair->next)
			last_pair = last_pair->next;
		last_pair->next = new_env_pair;
		new_env_pair->next = NULL;
	}
	else
	{
		(*env_list) = new_env_pair;
		new_env_pair->next = NULL;
	}
}

char	**check_array(char **array, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}
