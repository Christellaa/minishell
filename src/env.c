/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:45:25 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/11 16:25:47 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_keyval	*create_keyval_pair(char *raw, char *key, char *value,
		int is_exported)
{
	t_keyval	*new_env;

	new_env = malloc(sizeof(t_keyval));
	if (!new_env)
		return (NULL);
	new_env->raw = ft_strdup(raw);
	if (!raw)
		return (free(new_env), NULL);
	new_env->key = ft_strdup(key);
	if (!key)
		return (free(new_env), free(raw), NULL);
	new_env->value = ft_strdup(value);
	if (!value)
		return (free(new_env), free(raw), free(key), NULL);
	new_env->is_exported = is_exported;
	new_env->next = NULL;
	return (new_env);
}

t_keyval	*get_keyval_pair(char *current_env)
{
	t_keyval	*new_env;
	char		*raw;
	char		*key;
	char		*value;
	char		*equal_pos;

	equal_pos = ft_strchr(current_env, '=');
	if (!equal_pos)
		return (NULL);
	raw = ft_strdup(current_env);
	if (!raw)
		return (NULL);
	key = ft_substr(current_env, 0, equal_pos - current_env);
	if (!key)
		return (free(raw), NULL);
	value = get_value(equal_pos);
	if (!value)
		return (free(raw), free(key), NULL);
	new_env = create_keyval_pair(raw, key, value, 1);
	if (!new_env)
		return (free(raw), free(key), free(value), NULL);
	free(raw);
	free(key);
	free(value);
	return (new_env);
}

void	add_keyval_to_list(t_keyval **env_list, t_keyval *new_env)
{
	t_keyval	*last;

	if (!env_list || !new_env)
		return ;
	if (*env_list)
	{
		last = (*env_list);
		while (last->next)
			last = last->next;
		last->next = new_env;
		new_env->next = NULL;
	}
	else
	{
		new_env->next = NULL;
		(*env_list) = new_env;
	}
}

void	get_env_list(t_data *data, char **envp)
{
	t_keyval	*env;
	int			i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		env = get_keyval_pair(envp[i]);
		if (env)
			add_keyval_to_list(&data->env_list, env);
		i++;
	}
}
