/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:50:17 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/07 22:08:18 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_tools/parsing_tools.h"

int		create_and_add_node_to_list(t_data *data, t_exec **new_node);
void	create_exec_node(t_exec **new_node, t_data *data);
void	add_node_to_list(t_exec **exec_list, t_exec *node);
int		add_value_to_node(t_exec **node, char *value, int type, t_data *data);

int	create_exec_list(t_data *data)
{
	t_token	*token;
	t_exec	*new_node;

	token = data->token_list;
	while (token)
	{
		if (token == data->token_list)
		{
			if (!create_and_add_node_to_list(data, &new_node))
				return (0);
			if (!add_value_to_node(&new_node, token->value, token->type, data))
				return (0);
		}
		else if (token->type == PIPE)
		{
			if (!create_and_add_node_to_list(data, &new_node))
				return (0);
		}
		else if (!add_value_to_node(&new_node, token->value, token->type, data))
			return (0);
		token = token->next;
	}
	return (1);
}

int	create_and_add_node_to_list(t_data *data, t_exec **new_node)
{
	create_exec_node(new_node, data);
	if (!new_node)
		return (0);
	add_node_to_list(&(data->exec_list), *new_node);
	return (1);
}

void	create_exec_node(t_exec **new_node, t_data *data)
{
	*new_node = malloc(sizeof(t_exec));
	if (!new_node)
		return (print_error(0, NULL, data));
	(*new_node)->arg_list = NULL;
	(*new_node)->files = NULL;
	(*new_node)->pid = -1;
	(*new_node)->pipefd[0] = -1;
	(*new_node)->pipefd[1] = -1;
	(*new_node)->next = NULL;
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

int	add_value_to_node(t_exec **node, char *value, int type, t_data *data)
{
	if (type == ARG)
	{
		if (!add_arg_to_node(node, value))
			return (print_error(0, NULL, data), 0);
	}
	else if (type == FILENAME || type == INFILE || type == HEREDOC
		|| type == TRUNC || type == APPEND)
	{
		if (!add_file_to_node(node, value, type))
			return (print_error(0, NULL, data), 0);
	}
	return (1);
}
