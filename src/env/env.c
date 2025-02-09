/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:45:25 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/09 19:12:54 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	get_env_list(t_data *data, char **envp)
{
	t_env	*env_pair;
	int		i;

	env_pair = NULL;
	i = 0;
	while (envp[i])
	{
		env_pair = get_env_raw(envp[i], 1);
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

t_env	*get_env_raw(char *current_env_pair, int type)
{
	t_env	*new_env_pair;
	char	*raw;
	char	*equal_pos;

	raw = ft_strdup(current_env_pair);
	if (!raw)
		return (NULL);
	equal_pos = ft_strchr(raw, '=');
	new_env_pair = create_env_pair(raw, equal_pos, type);
	if (!new_env_pair)
		return (NULL);
	return (new_env_pair);
}
