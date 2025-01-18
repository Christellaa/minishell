/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:50:17 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/18 16:59:58 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_exec_node(t_exec **new_node)
{
	*new_node = malloc(sizeof(t_exec));
	if (!new_node)
	{
		print_error(6, NULL, NULL);
		return ;
	}
	(*new_node)->arg_list = NULL;
	(*new_node)->redirs = NULL;
	(*new_node)->skip = 0;
	(*new_node)->fdpipe[0] = STDIN_FILENO;
	(*new_node)->fdpipe[1] = STDOUT_FILENO;
	(*new_node)->next = NULL;
}

void	add_value_to_node(t_exec **node, char *value, int type)
{
	if (type == ARG)
		add_arg_to_node(node, value);
	else if (type == FILENAME || type == INFILE || type == HEREDOC
		|| type == TRUNC || type == APPEND)
		add_redir_to_node(node, value, type);
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
