/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:58:42 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/09 19:03:20 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**create_raws(void);
char	**create_keys(void);
char	**create_values(void);
int		*create_exported(void);

int	create_env_list(t_data *data)
{
	t_env	*new_node;
	char	**arrays[3];
	int		*exported;
	int		i;

	arrays[0] = create_raws();
	arrays[1] = create_keys();
	arrays[2] = create_values();
	exported = create_exported();
	if (!arrays[0] || !arrays[1] || !arrays[2] || !exported)
		return (print_error(0, NULL, data), 0);
	i = -1;
	while (arrays[0][++i])
	{
		new_node = create_env_node(arrays[0][i], arrays[1][i], arrays[2][i],
				exported[i]);
		if (!new_node)
			return (print_error(0, NULL, data), 0);
		add_env_node_to_list(&data->env_list, new_node);
	}
	return (1);
}

char	**create_raws(void)
{
	char	**raw;

	raw = malloc(6 * sizeof(char *));
	if (!raw)
		return (NULL);
	raw[0] = ft_strdup("OLDPWD");
	raw[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	raw[2] = ft_strdup("SHLVL=1");
	raw[3] = ft_strdup("_=/usr/bin/env");
	raw[4] = get_path_from_its_file();
	raw[5] = NULL;
	return (check_array(raw, 0, 5));
}

char	**create_keys(void)
{
	char	**keys;

	keys = malloc(6 * sizeof(char *));
	if (!keys)
		return (NULL);
	keys[0] = ft_strdup("OLDPWD");
	keys[1] = ft_strdup("PWD");
	keys[2] = ft_strdup("SHLVL");
	keys[3] = ft_strdup("_");
	keys[4] = ft_strdup("PATH");
	keys[5] = NULL;
	return (check_array(keys, 0, 5));
}

char	**create_values(void)
{
	char	**values;
	char	*path;
	char	*pos;

	path = get_path_from_its_file();
	pos = ft_strchr(path, '=');
	path = pos + 1;
	values = malloc(6 * sizeof(char *));
	if (!values)
		return (NULL);
	values[0] = NULL;
	values[1] = getcwd(NULL, 0);
	values[2] = ft_strdup("1");
	values[3] = ft_strdup("./minishell");
	values[4] = ft_strdup(path);
	values[5] = NULL;
	return (check_array(values, 1, 5));
}

int	*create_exported(void)
{
	int	*exported;

	exported = malloc(5 * sizeof(int));
	if (!exported)
		return (NULL);
	exported[0] = IN_EXPORT;
	exported[1] = IN_ENV | IN_EXPORT;
	exported[2] = IN_ENV | IN_EXPORT;
	exported[3] = IN_ENV;
	exported[4] = 0;
	return (exported);
}
