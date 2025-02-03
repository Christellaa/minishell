/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:58:42 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/03 12:42:08 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_raws(void);
char	**create_keys(void);
char	**create_values(void);
int		*create_exported(void);

int	create_env_list(t_data *data)
{
	t_env	*new_node;
	char	**raw;
	char	**keys;
	char	**values;
	int		*exported;
	int		i;

	i = -1;
	raw = create_raws();
	keys = create_keys();
	values = create_values();
	exported = create_exported();
	if (!raw || !keys || !values || !exported)
		return (print_error(0, NULL, data), 0);
	while (raw[++i])
	{
		new_node = create_env_node(raw[i], keys[i], values[i], exported[i]);
		if (!new_node)
			return (print_error(0, NULL, data), 0);
		add_env_node_to_list(&data->env_list, new_node);
	}
	return (1);
}

char	**create_raws(void)
{
	char	**raw;
	int		i;

	raw = malloc(4 * sizeof(char *));
	if (!raw)
		return (NULL);
	raw[0] = ft_strdup("OLDPWD");
	raw[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
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

char	**create_keys(void)
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

char	**create_values(void)
{
	char	**values;
	int		i;

	values = malloc(4 * sizeof(char *));
	if (!values)
		return (NULL);
	values[0] = NULL;
	values[1] = getcwd(NULL, 0);
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

int	*create_exported(void)
{
	int	*exported;

	exported = malloc(4 * sizeof(int));
	if (!exported)
		return (NULL);
	exported[0] = IN_EXPORT;
	exported[1] = IN_ENV | IN_EXPORT;
	exported[2] = IN_ENV | IN_EXPORT;
	exported[3] = IN_ENV;
	return (exported);
}
