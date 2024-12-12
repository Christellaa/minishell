/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:29 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/12 15:25:14 by cde-sous         ###   ########.fr       */
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
		if (check_forbidden_chars(tmp) == -1)
			return (-1); // forbidden char found
		if (check_double_pipe(tmp) == -1)
			return (-1); // pipe after pipe
		tmp = tmp->next;
	}
	return (0);
}

int	parser(t_data *data)
{
	int	err;

	if (!data->token_list)
	{
		printf("empty token list\n"); // not an error
		return (-1);
	}
	err = check_assignment(&data->token_list);
	if (err == -1)
		return (-1); // need a word before '='
	else if (err == -2)
		return (-1); // malloc fail
	if (check_token_list(&data->token_list, err) == -1)
		return (-1);
	delete_empty_quotes(&data->token_list);
	if (!data->token_list)
	{
		printf("token list now empty\n");
		// if it was just "" or '' as pipeline => error: cmd not found
		return (-1);
	}
	// delete first quotes surrounding word
	// check what type of WORD: CMD, ARG, FILENAME
	// check if order of pipeline is valid
	return (0);
}
