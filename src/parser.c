/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:29 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/13 14:26:24 by cde-sous         ###   ########.fr       */
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

int	check_pipeline_order(t_token *token_list)
{
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
	check_pipeline_order(data->token_list);
	return (0);
}
