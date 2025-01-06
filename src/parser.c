/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:29 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/06 15:12:42 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_token_list(t_token **token_list, int err)
{
	t_token	*tmp;

	tmp = *token_list;
	while (tmp)
	{
		err = check_chevrons(tmp);
		if (err == -1)
			return (-1); // too many chevrons
		else if (err == -2)
			return (-1); // no filename after chevrons
		if (check_quotes_close(tmp) == -1)
			return (-1); // ' or \" not closed
		if (check_double_pipe(tmp) == -1)
			return (-1); // pipe after pipe
		tmp = tmp->next;
	}
	return (0);
}

void	replace_type_word(t_token **token_list)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = *token_list;
	prev = *token_list;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (prev != tmp)
			{
				determine_token_type(prev, &tmp);
				prev = prev->next;
			}
			else
				tmp->type = CMD;
		}
		tmp = tmp->next;
	}
}

int	is_order_valid(t_token *current, t_token *next)
{
	if (current->type == ASSIGNMENT || current->type == FILENAME)
		// impossible to have ARG/FILENAME and everything else is good
		return (1);
	else if (current->type == INFILE || current->type == HEREDOC
		|| current->type == TRUNC || current->type == APPEND)
		return (next && next->type == FILENAME);
	else if (current->type == PIPE) // if first token, return 0 because bad
		return (next && next->type != PIPE);
	else if (current->type == CMD || current->type == ARG)
		return (!next || (next->type != CMD && next->type != ASSIGNMENT));
	return (0);
}

/*
ASSIGNMENT || FILENAME:
	- NULL
	- CHEVRON
	- ASSIGNMENT
	- CMD
	- PIPE
CHEVRON:
	- next is NOT NULL!
	- FILENAME
PIPE:
	- next is NOT NULL!
	- CHEVRON
	- ASSIGNMENT
	- CMD
CMD || ARG:
	- NULL
	- CHEVRON
	- ARG
	- PIPE
*/

int	validate_pipeline(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (!is_order_valid(current, current->next))
		{
			printf("AAAAA\n");
			return (0);
		}
		printf("BBBBB\n");
		current = current->next;
	}
	return (1);
}

int	parser(t_data *data)
{
	int	err;

	if (!data->token_list)
		return (-1); // empty token list, not an error
	err = check_assignment(&data->token_list);
	if (err == -1)
		return (-1); // need a word before '='
	else if (err == -2)
		return (-1); // malloc fail
	if (check_token_list(&data->token_list, err) == -1)
		return (-1);
	delete_empty_quotes(&data->token_list);
	if (!data->token_list)
		return (-1); // empty token list,
						// error if it was just "" or '' (=> cmd not found)
	replace_type_word(&data->token_list);
	// check if order of pipeline is valid
	if (!validate_pipeline(data->token_list))
		return (-1); // invalid pipeline
	return (0);
}

/*
TODO:
1:
	redo replace_type_word for:
		when ASSIGNMENT is after CMD/ARG => replace it as ARG
		eg: ls a=b
		eg2: ls a=b -l
		eg3: ls -l a=b

	then modify is_order_valid of validate_pipeline of parser:
		for if current type is CMD or ARG => delete returning for ASSIGNMENT bc no longer ASSIGNMENT after CMD,
			only ARG

2:
	in is_order_valid in validate_pipeline,
		make sure PIPE isn't the first token, otherwise bad pipeline
3:
	clean up every function by:
		- deleting useless parts (eg: because they're reused during another part)
		- make more meaningful names
		- compact the function
*/
