/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:25:16 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/09 19:19:08 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*get_env_value(char *equal_pos);
t_env	*create_env_pair_by_type(char *raw, char *key, char *value, int type);

t_env	*create_env_pair(char *raw, char *equal_pos, int type)
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
		new_env_pair = create_env_pair_by_type(raw, key, value, type);
	}
	return (new_env_pair);
}

t_env	*create_env_pair_by_type(char *raw, char *key, char *value, int type)
{
	t_env	*new_env_pair;

	if (ft_strcmp(key, "_") == 0)
		new_env_pair = create_env_node(raw, key, value, IN_ENV);
	else if (type == 0)
		new_env_pair = create_env_node(raw, key, value, 0);
	else
		new_env_pair = create_env_node(raw, key, value, IN_ENV | IN_EXPORT);
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
