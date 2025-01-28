/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:50:39 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/28 10:16:11 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg	*find_last_arg(t_arg *arg);
t_files	*find_last_file(t_files *file);

int	add_arg_to_node(t_exec **node, char *value)
{
	t_arg	*last_arg;

	if (!(*node)->arg_list)
	{
		(*node)->arg_list = malloc(sizeof(t_arg));
		if (!(*node)->arg_list)
			return (0);
		(*node)->arg_list->value = value;
		(*node)->arg_list->next = NULL;
	}
	else
	{
		last_arg = find_last_arg((*node)->arg_list);
		last_arg->next = malloc(sizeof(t_arg));
		if (!last_arg->next)
			return (0);
		last_arg->next->value = value;
		last_arg->next->next = NULL;
	}
	return (1);
}

t_arg	*find_last_arg(t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	add_file_to_node(t_exec **node, char *value, int type)
{
	t_files	*last_file;

	if (!(*node)->files)
	{
		(*node)->files = malloc(sizeof(t_files));
		if (!(*node)->files)
			return (0);
		(*node)->files->value = value;
		(*node)->files->type = type;
		(*node)->files->next = NULL;
	}
	else
	{
		last_file = find_last_file((*node)->files);
		last_file->next = malloc(sizeof(t_files));
		if (!last_file->next)
			return (0);
		last_file->next->value = value;
		last_file->next->type = type;
		last_file->next->next = NULL;
	}
	return (1);
}

t_files	*find_last_file(t_files *file)
{
	t_files	*tmp;

	tmp = file;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
