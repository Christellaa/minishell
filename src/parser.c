/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:29 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/10 17:03:37 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(t_data *data)
{
	int err = 0;
	if (!data->token_list)
	{
		printf("empty token list\n");
		return (-1);
	}
	// CHEVRONS:
	// - check how many CHEVRON
	// - check if a WORD follows a CHEVRON
	err = check_chevrons(data->token_list);
	if (err == -1)
	{
		printf("too many chevrons\n");
		return (-1);
	}
	if (err == -2)
	{
		printf("no filename after chevrons\n");
		return (-1);
	}
	return (0);
	// ASSIGNMENT:
	// - check if there's something before '='
	// err = check_assignment(data->token_list);
	// PIPE:
	// - check if next is also a PIPE
	// QUOTES :
	// - check if " or ' finishes, even if nestled
	// FORBIDDEN CHARS:
	// - check forbidden chars outside of " and '
	// EMPTY TOKEN :
	// - delete empty token values ("", '')
	// WORD:
	// - check what type of WORD it is: CMD, ARG, FILENAME
	// ORDER:
	// - check order of pipeline
}