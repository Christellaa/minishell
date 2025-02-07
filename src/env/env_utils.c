/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:25:16 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/07 22:14:18 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*get_env_value(char *equal_pos);

t_env	*create_env_pair(char *raw, char *equal_pos)
{
	t_env	*new_env_pair;
	char	*key;
	char	*value;

	if (!equal_pos)
	{
		key = ft_strdup(raw);
		if (!key)
			return (NULL);
		new_env_pair = create_env_node(raw, key, NULL, IN_EXPORT);
	}
	else
	{
		key = ft_substr(raw, 0, equal_pos - raw);
		if (!key)
			return (NULL);
		value = get_env_value(equal_pos);
		if (!value)
			return (free(key), NULL);
		if (ft_strcmp(key, "_") == 0)
			new_env_pair = create_env_node(raw, key, value, IN_ENV);
		else
			new_env_pair = create_env_node(raw, key, value, IN_ENV | IN_EXPORT);
	}
	return (new_env_pair);
}

char	*get_env_value(char *equal_pos)
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
