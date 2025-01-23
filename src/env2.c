/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:58:42 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/23 11:05:49 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_raw(void)
{
	char	**raw;
	int		i;

	raw = malloc(4 * sizeof(char *));
	if (!raw)
		return (NULL);
	raw[0] = ft_strdup("OLDPWD");
	raw[1] = ft_strdup("PWD=getcwd_to_do");
	raw[2] = ft_strdup("SHLVL=1");
	raw[3] = ft_strdup("_=/usr/bin/env");
	i = -1;
	while (++i < 4)
	{
		if (!raw[i])
		{
			while (--i >= 0)
				free(raw[i]);
			free(raw);
			return (NULL);
		}
	}
	return (raw);
}

char	**get_keys(void)
{
	char	**keys;
	int		i;

	keys = malloc(4 * sizeof(char *));
	if (!keys)
		return (NULL);
	keys[0] = ft_strdup("OLDPWD");
	keys[1] = ft_strdup("PWD");
	keys[2] = ft_strdup("SHLVL");
	keys[3] = ft_strdup("_");
	i = -1;
	while (++i < 4)
	{
		if (!keys[i])
		{
			while (--i >= 0)
				free(keys[i]);
			free(keys);
			return (NULL);
		}
	}
	return (keys);
}

char	**get_values(void)
{
	char	**values;
	int		i;

	values = malloc(4 * sizeof(char *));
	if (!values)
		return (NULL);
	values[0] = NULL;
	values[1] = ft_strdup("getcwd_to_do");
	values[2] = ft_strdup("1");
	values[3] = ft_strdup("./minishell");
	i = 0;
	while (++i < 4)
	{
		if (!values[i])
		{
			while (--i >= 0)
				free(values[i]);
			free(values);
			return (NULL);
		}
	}
	return (values);
}

int	*get_exported(void)
{
	int	*exported;

	exported = malloc(4 * sizeof(int));
	if (!exported)
		return (NULL);
	exported[0] = 0;
	exported[1] = 1;
	exported[2] = 1;
	exported[3] = 2;
	return (exported);
}

int	create_env_list2(t_data *data)
{
	t_env	*new_node;
	char	**raw;
	char	**keys;
	char	**values;
	int		*exported;

	raw = get_raw();
	keys = get_keys();
	values = get_values();
	exported = get_exported();
	if (!raw || !keys || !values || !exported)
		return (print_error(6, NULL, NULL), 0);
	while (*raw)
	{
		new_node = create_env_node(*raw, *keys, *values, *exported);
		if (!new_node)
			return (print_error(6, NULL, NULL), 0);
		add_env_node_to_list(&data->env_list, new_node);
		raw++;
		keys++;
		values++;
		exported++;
	}
	return (1);
}
