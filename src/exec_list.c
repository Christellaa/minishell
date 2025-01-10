/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:50:17 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/10 16:50:20 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_exec	*create_exec_node(void)
{
	t_exec	*new_node;

	new_node = malloc(sizeof(t_exec));
	if (!new_node)
	{
		printf("Malloc error\n");
		return (NULL);
	}
	new_node->cmd = NULL;
	new_node->arg_list = malloc(sizeof(new_node->arg_list));
	new_node->redirs = malloc(sizeof(new_node->redirs));
	new_node->arg_list->value = NULL;
	new_node->arg_list->next = NULL;
	new_node->redirs->value = NULL;
	new_node->redirs->type = -1;
	new_node->redirs->next = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_value_to_node(t_exec **node, char *value, int type)
{
	printf("value: %s\n", value);
	if (type == CMD)
	{
		(*node)->cmd = value;
	}
	else if (type == ARG)
		(*node)->arg_list->value = value;
	else if (type == FILENAME || type == INFILE || type == HEREDOC
		|| type == TRUNC || type == APPEND)
	{
		(*node)->redirs->value = value;
		(*node)->redirs->type = type;
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

int	create_and_add_node_to_list(t_data *data, t_exec *new_node)
{
	new_node = create_exec_node();
	if (!new_node)
		return (-1);
	add_node_to_list(&(data->exec_list), new_node);
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
			if (create_and_add_node_to_list(data, new_node) == -1)
				return (-1);
			add_value_to_node(&new_node, token->value, token->type);
		}
		else if (token->type == PIPE)
		{
			if (create_and_add_node_to_list(data, new_node) == -1)
				return (-1);
		}
		else
			add_value_to_node(&new_node, token->value, token->type);
		token = token->next;
	}
	// cleanup(data, 0);
	return (0);
}
