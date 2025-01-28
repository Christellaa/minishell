/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:45:25 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/28 10:00:59 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env_raw(char *current_env_pair);
t_env	*create_env_pair(char *raw, char *equal_pos);
t_env	*create_env_node(char *raw, char *key, char *value, int show_in_env);
void	add_env_node_to_list(t_env **env_list, t_env *new_env_pair);

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
		return (free(raw), NULL);
	return (free(raw), new_env_pair);
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
		value = NULL;
		new_env_pair = create_env_node(raw, key, value, 0);
	}
	else
	{
		key = ft_substr(raw, 0, equal_pos - raw);
		if (!key)
			return (NULL);
		value = get_env_value(equal_pos);
		if (!value)
			return (free(key), NULL);
		new_env_pair = create_env_node(raw, key, value, 1);
	}
	return (free(key), free(value), new_env_pair);
}

t_env	*create_env_node(char *raw, char *key, char *value, int show_in_env)
{
	t_env	*new_env_pair;

	new_env_pair = malloc(sizeof(t_env));
	if (!new_env_pair)
		return (NULL);
	new_env_pair->raw = ft_strdup(raw);
	if (!new_env_pair->raw)
		return (free(new_env_pair), NULL);
	new_env_pair->key = ft_strdup(key);
	if (!new_env_pair->key)
		return (free(new_env_pair->raw), free(new_env_pair), NULL);
	if (!value)
		new_env_pair->value = NULL;
	new_env_pair->value = ft_strdup(value);
	if (value && !new_env_pair->value)
		return (free(new_env_pair->raw), free(new_env_pair->key),
			free(new_env_pair), NULL);
	new_env_pair->show_in_env = show_in_env;
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
			return (print_error(6, NULL, NULL), 0);
		add_env_node_to_list(&data->env_list, env_pair);
		i++;
	}
	if (!*envp)
		if (!create_env_list(data))
			return (0);
	if (!data->env_list)
		return (0);
	return (1);
}
