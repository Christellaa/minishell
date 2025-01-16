/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:45:25 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/16 14:02:51 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*create_env_node(char *raw, char *key, char *value, int show_in_env)
{
	t_env	*new_env_pair;

	new_env_pair = malloc(sizeof(t_env));
	if (!new_env_pair)
		return (NULL);
	new_env_pair->raw = ft_strdup(raw);
	if (!raw)
		return (free(new_env_pair), NULL);
	new_env_pair->key = ft_strdup(key);
	if (!key)
		return (free(new_env_pair), free(raw), NULL);
	new_env_pair->value = ft_strdup(value);
	if (!value)
		return (free(new_env_pair), free(raw), free(key), NULL);
	new_env_pair->show_in_env = show_in_env;
	new_env_pair->next = NULL;
	return (new_env_pair);
}

t_env	*get_env_pair(char *current_env_pair)
{
	t_env	*new_env_pair;
	char	*raw;
	char	*key;
	char	*value;
	char	*equal_pos;

	equal_pos = ft_strchr(current_env_pair, '=');
	if (!equal_pos)
		return (NULL);
	raw = ft_strdup(current_env_pair);
	if (!raw)
		return (NULL);
	key = ft_substr(current_env_pair, 0, equal_pos - current_env_pair);
	if (!key)
		return (free(raw), NULL);
	value = get_value(equal_pos);
	if (!value)
		return (free(raw), free(key), NULL);
	new_env_pair = create_env_node(raw, key, value, 1);
	if (!new_env_pair)
		return (free(raw), free(key), free(value), NULL);
	free(raw);
	free(key);
	free(value);
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

void	create_env_list(t_data *data, char **envp)
{
	t_env	*env_pair;
	int		i;

	env_pair = NULL;
	i = 0;
	while (envp[i])
	{
		env_pair = get_env_pair(envp[i]);
		if (env_pair)
			add_env_node_to_list(&data->env_list, env_pair);
		i++;
	}
}
