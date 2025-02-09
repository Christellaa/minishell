/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:30:32 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/09 17:14:19 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		is_first_char_valid(char *value, t_data *data);

t_env	*insertion_sort(t_env *sorted_list, t_env *new_node)
{
	t_env	*current;

	if (!sorted_list || ft_strcmp(new_node->raw, sorted_list->raw) < 0)
	{
		new_node->next = sorted_list;
		return (new_node);
	}
	current = sorted_list;
	while (current->next && ft_strcmp(current->next->raw, new_node->raw) < 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
	return (sorted_list);
}

int	is_key_valid(char *value, t_data *data)
{
	int	i;

	i = 0;
	if (!is_first_char_valid(value, data))
		return (0);
	while (value[i] && value[i] != '=')
	{
		if ((!ft_isalpha(value[i]) && value[i] != '_'))
		{
			ft_dprintf(STDERR_FILENO, "export: '%s': not a valid identifier\n",
				value);
			data->exit_code = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_first_char_valid(char *value, t_data *data)
{
	if (value[0] == '-')
	{
		ft_dprintf(STDERR_FILENO, "export: %c%c: invalid option\n", value[0],
			value[1]);
		data->exit_code = 2;
		return (0);
	}
	else if (value[0] == '=')
	{
		ft_dprintf(STDERR_FILENO, "export: '%s': not a valid identifier\n",
			value);
		data->exit_code = 1;
		return (0);
	}
	return (1);
}

void	replace_env_pair(t_env *current_env, t_env *new_node)
{
	free(current_env->raw);
	free(current_env->key);
	if (current_env->value)
		free(current_env->value);
	current_env->raw = new_node->raw;
	current_env->key = new_node->key;
	if (!new_node->value)
		current_env->value = NULL;
	else
		current_env->value = new_node->value;
	current_env->is_exported = new_node->is_exported;
	free(new_node);
}
