/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:50:39 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/17 14:51:00 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_redirs	*find_last_redir(t_redirs *redir)
{
	t_redirs	*tmp;

	tmp = redir;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_arg_to_node(t_exec **node, char *value)
{
	t_arg	*last_arg;

	if (!(*node)->arg_list)
	{
		(*node)->arg_list = malloc(sizeof(t_arg));
		if (!(*node)->arg_list)
			return (print_error(6, NULL, NULL));
		(*node)->arg_list->value = value;
		(*node)->arg_list->next = NULL;
	}
	else
	{
		last_arg = find_last_arg((*node)->arg_list);
		last_arg->next = malloc(sizeof(t_arg));
		if (!last_arg->next)
			return (print_error(6, NULL, NULL));
		last_arg->next->value = value;
		last_arg->next->next = NULL;
	}
}

void	add_redir_to_node(t_exec **node, char *value, int type)
{
	t_redirs	*last_redir;

	if (!(*node)->redirs)
	{
		(*node)->redirs = malloc(sizeof(t_redirs));
		if (!(*node)->redirs)
			return (print_error(6, NULL, NULL));
		(*node)->redirs->value = value;
		(*node)->redirs->type = type;
		(*node)->redirs->next = NULL;
	}
	else
	{
		last_redir = find_last_redir((*node)->redirs);
		last_redir->next = malloc(sizeof(t_redirs));
		if (!last_redir->next)
			return (print_error(6, NULL, NULL));
		last_redir->next->value = value;
		last_redir->next->type = type;
		last_redir->next->next = NULL;
	}
}
