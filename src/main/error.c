/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:16:12 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 16:38:03 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		get_err_code(int flag);

void	print_error(int flag, char *error, t_data *data)
{
	if (data)
		data->exit_code = get_err_code(flag);
	if (flag == 0) // 1
		ft_dprintf(STDERR_FILENO, "%s\n", MALLOC_ERR);
	else if (flag == 1) // 1
		ft_dprintf(STDERR_FILENO, "%s%s\n", error, FILE_ERR);
	else if (flag == 2) // 1
		ft_dprintf(STDERR_FILENO, "%s%s\n", error, FILE_DENY);
	else if (flag == 3) // 1
		ft_dprintf(STDERR_FILENO, "%s\n" TOO_MANY_ARG);
	else if (flag == 4) // 1; function errors
		ft_dprintf(STDERR_FILENO, "%s error\n", error);
	else if (flag == 5) // 2
		ft_dprintf(STDERR_FILENO, "%s '%s'\n" SYNTAX_ERR, error);
	else if (flag == 6) // 2
		ft_dprintf(STDERR_FILENO, "%s\n" QUOTE_ERR);
	else if (flag == 7) // 126
		ft_dprintf(STDERR_FILENO, "%s%s\n", error, FILE_DENY);
	else if (flag == 8) // 127
		ft_dprintf(STDERR_FILENO, "%s%s\n", error, CMD_ERR);
	else if (flag == 9) // 127
		ft_dprintf(STDERR_FILENO, "%s%s\n", error, FILE_ERR);
}

int	get_err_code(int flag)
{
	int	code;

	if (flag >= 0 && flag <= 4)
		code = 1;
	else if (flag >= 5 && flag <= 6)
		code = 2;
	else if (flag == 7)
		code = 126;
	else if (flag == 8 || flag == 9)
		code = 127;
	return (code);
}
