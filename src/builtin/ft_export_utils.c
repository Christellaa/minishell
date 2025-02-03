/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:30:32 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/02 18:31:11 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (!ft_isalpha(*value) && *value != '_')
	{
		ft_dprintf(STDERR_FILENO, "export: '%s': not a valid identifier\n",
			value);
		data->exit_code = 1;
		return (0);
	}
	return (1);
}
