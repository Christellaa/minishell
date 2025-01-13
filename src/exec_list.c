/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:50:17 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/13 14:30:19 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_exec_node(t_exec **new_node)
{
	*new_node = malloc(sizeof(t_exec));
	if (!new_node)
	{
		printf("Malloc error\n");
		return ;
	}
	(*new_node)->cmd = NULL;
	(*new_node)->arg_list = NULL;
	(*new_node)->redirs = NULL;
	(*new_node)->next = NULL;
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

void	add_value_to_node(t_exec **node, char *value, int type)
{
	t_arg		*last_arg;
	t_redirs	*last_redir;

	if (type == CMD)
		(*node)->cmd = value;
	else if (type == ARG)
	{
		if (!(*node)->arg_list)
		{
			(*node)->arg_list = malloc(sizeof(t_arg)); // check fail
			(*node)->arg_list->value = value;
			(*node)->arg_list->next = NULL;
		}
		else
		{
			last_arg = find_last_arg((*node)->arg_list);
			last_arg->next = malloc(sizeof(t_arg)); // check fail
			last_arg->next->value = value;
			last_arg->next->next = NULL;
		}
	}
	else if (type == FILENAME || type == INFILE || type == HEREDOC
		|| type == TRUNC || type == APPEND)
	{
		if (!(*node)->redirs)
		{
			(*node)->redirs = malloc(sizeof(t_redirs)); // check fail
			(*node)->redirs->value = value;
			(*node)->redirs->type = type;
			(*node)->redirs->next = NULL;
		}
		else
		{
			last_redir = find_last_redir((*node)->redirs);
			last_redir->next = malloc(sizeof(t_redirs)); // check fail
			last_redir->next->value = value;
			last_redir->next->type = type;
			last_redir->next->next = NULL;
		}
	}
}

void	add_node_to_list(t_exec **exec_list, t_exec *node)
{
	t_exec	*last;

	if (!exec_list || !node)
		return ;
	if (*exec_list)
	{
		last = (*exec_list);
		while (last->next)
			last = last->next;
		last->next = node;
	}
	else
		*exec_list = node;
}

int	create_and_add_node_to_list(t_data *data, t_exec **new_node)
{
	create_exec_node(new_node);
	if (!new_node)
		return (-1);
	add_node_to_list(&(data->exec_list), *new_node);
	return (0);
}

int	create_exec_list(t_data *data)
{
	t_token	*token;
	t_exec	*new_node;

	token = data->token_list;
	while (token)
	{
		if (token == data->token_list)
		{
			if (create_and_add_node_to_list(data, &new_node) == -1)
				return (-1);
			add_value_to_node(&new_node, token->value, token->type);
		}
		else if (token->type == PIPE)
		{
			if (create_and_add_node_to_list(data, &new_node) == -1)
				return (-1);
		}
		else
			add_value_to_node(&new_node, token->value, token->type);
		token = token->next;
	}
	return (0);
}
