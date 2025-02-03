/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:45:25 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/03 16:20:41 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_env_raw(char *current_env_pair);
t_env	*create_env_pair(char *raw, char *equal_pos);
t_env	*create_env_node(char *raw, char *key, char *value, int is_exported);
void	add_env_node_to_list(t_env **env_list, t_env *new_env_pair);

int	get_env_list(t_data *data, char **envp)
{
	t_env	*env_pair;
	int		i;

	env_pair = NULL;
	i = 0;
	while (envp[i])
	{
		env_pair = get_env_raw(envp[i]);
		if (!env_pair)
			return (print_error(0, NULL, data), 0);
		add_env_node_to_list(&data->env_list, env_pair);
		i++;
	}
	if (!*envp)
		if (!create_env_list(data))
			return (0);
	if (!update_shlvl(data->env_list, data))
		return (0);
	if (!data->env_list)
		return (0);
	return (1);
}

t_env	*get_env_raw(char *current_env_pair)
{
	t_env	*new_env_pair;
	char	*raw;
	char	*equal_pos;

	raw = ft_strdup(current_env_pair);
	if (!raw)
		return (NULL);
	equal_pos = ft_strchr(raw, '=');
	new_env_pair = create_env_pair(raw, equal_pos);
	if (!new_env_pair)
		return (NULL);
	return (new_env_pair);
}

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
