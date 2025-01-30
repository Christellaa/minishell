/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:16:12 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/30 09:30:09 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_err_code(int flag);

int	print_error(int flag, char *error, char *option, t_data *data)
{
	(void)option;
	if (data)
		data->exit_code = get_err_code(flag);
	if (flag == 0) // 1
		printf("%s\n", MALLOC_ERR);
	else if (flag == 1) // 1
		printf("%s%s\n", error, FILE_ERR);
	else if (flag == 2) // 1
		printf("%s%s\n", error, FILE_DENY);
	else if (flag == 3) // 1
		printf("%s\n", TOO_MANY_ARG);
	else if (flag == 4) // 1; function errors
		printf("%s error\n", error);
	else if (flag == 5) // 2
		printf("%s '%s'\n", SYNTAX_ERR, error);
	else if (flag == 6) // 2
		printf("%s\n", QUOTE_ERR);
	// else if (flag == 7) // 2
	// printf("%s%s '%s'\n", error, OPTION_ERR, option);
	else if (flag == 8) // 127
		printf("%s%s\n", error, CMD_ERR);
	else if (flag == 9) // 127
		printf("%s%s\n", error, FILE_ERR);
	else if (flag == 10) // 126
		printf("%s%s\n", error, FILE_DENY);
	if (data)
		return (data->exit_code);
	return (1);
}

int	get_err_code(int flag)
{
	int	code;

	if (flag >= 0 && flag <= 4)
		code = 1;
	else if (flag >= 5 && flag <= 7)
		code = 2;
	else if (flag == 8 || flag == 9)
		code = 127;
	else if (flag == 10)
		code = 126;
	return (code);
}
