/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:04:41 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 18:54:20 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "builtin.h"

t_env	*order_export_list(t_env *list);
void	print_export_list(t_env *ordered_list);
void	export_each_arg(t_exec *exec_node, t_data *data);
int		replace_existing_env_pair(t_env *new_node, t_env **list);

void	ft_export(t_data *data, t_exec *exec_node)
{
	t_arg	*args;
	t_env	*ordered_list;

	args = exec_node->arg_list->next;
	if (!args)
	{
		ordered_list = order_export_list(data->env_list);
		if (!ordered_list)
			return (print_error(0, NULL, data));
		print_export_list(ordered_list);
		free_env(ordered_list);
		return ;
	}
	export_each_arg(exec_node, data);
	return ;
}

t_env	*order_export_list(t_env *list)
{
	t_env	*sorted_list;
	t_env	*current;
	t_env	*new_node;

	sorted_list = NULL;
	current = list;
	while (current)
	{
		new_node = get_env_raw(current->raw);
		if (!new_node)
			return (NULL);
		sorted_list = insertion_sort(sorted_list, new_node);
		current = current->next;
	}
	return (sorted_list);
}

void	print_export_list(t_env *ordered_list)
{
	while (ordered_list)
	{
		if (ordered_list->is_exported & IN_EXPORT)
		{
			printf("export %s", ordered_list->key);
			if (ordered_list->value)
				printf("=\"%s\"\n", ordered_list->value);
			else
				printf("\n");
		}
		ordered_list = ordered_list->next;
	}
}

void	export_each_arg(t_exec *exec_node, t_data *data)
{
	t_arg	*args;
	t_env	*new_env_pair;

	args = exec_node->arg_list;
	args = args->next;
	while (args)
	{
		if (!is_key_valid(args->value, data))
		{
			args = args->next;
			continue ;
		}
		new_env_pair = get_env_raw(args->value);
		if (!new_env_pair)
			return (print_error(0, NULL, data));
		if (!replace_existing_env_pair(new_env_pair, &data->env_list))
			add_env_node_to_list(&data->env_list, new_env_pair);
		args = args->next;
	}
	return ;
}

int	replace_existing_env_pair(t_env *new_node, t_env **list)
{
	t_env	*current_env;

	current_env = *list;
	while (current_env)
	{
		if (ft_strcmp(new_node->key, current_env->key) == 0)
		{
			if (!ft_strchr(new_node->raw, '='))
				return (1);
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
			return (1);
		}
		current_env = current_env->next;
	}
	return (0);
}
