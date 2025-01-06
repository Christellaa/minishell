/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:29 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/06 16:46:15 by cde-sous         ###   ########.fr       */
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
	while (tmp)
	{
		if (tmp->type == ASSIGNMENT)
		{
			if (*token_list != tmp)
			{
				prev = get_prev_token(*token_list, tmp);
				if (prev->type == CMD || prev->type == ARG)
					tmp->type = ARG;
			}
		}
		else if (tmp->type == WORD)
		{
			if (*token_list != tmp)
				determine_token_type(token_list, &tmp);
			else
				tmp->type = CMD;
		}
		tmp = tmp->next;
	}
}

int	is_order_valid(t_token *list, t_token *current, t_token *next)
{
	if (current->type == ASSIGNMENT || current->type == FILENAME)
		return (1);
	else if (current->type == INFILE || current->type == HEREDOC
		|| current->type == TRUNC || current->type == APPEND)
		return (next && next->type == FILENAME);
	else if (current->type == PIPE)
	{
		if (current != list)
			return (next && next->type != PIPE);
		return (0);
	}
	else if (current->type == CMD || current->type == ARG)
		return (!next || next->type != CMD);
	return (0);
}

int	validate_pipeline(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (!is_order_valid(token_list, current, current->next))
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
		return (-1); // invalid pipeline order
	return (0);
}

/*
TODO:
3:
	clean up every function by:
		- deleting useless parts (eg: because they're reused during another part)
		- make more meaningful names
		- compact the function
*/
