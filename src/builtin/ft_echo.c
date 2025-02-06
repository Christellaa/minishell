/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:09:26 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 13:23:45 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		is_newline(char *arg_value);

void	ft_echo(t_data *data, t_exec *exec_node)
{
	t_arg	*arg;
	int		has_newline;

	arg = exec_node->arg_list->next;
	has_newline = 1;
	(void)data;
	if (!arg)
		printf("\n");
	while (is_newline(arg->value))
	{
		has_newline = 0;
		arg = arg->next;
	}
	while (arg)
	{
		printf("%s", arg->value);
		if (arg->next)
			printf(" ");
		arg = arg->next;
	}
	if (has_newline)
		printf("\n");
}

int	is_newline(char *arg_value)
{
	int	i;

	i = 0;
	if (arg_value[i] != '-')
		return (0);
	i++;
	while (arg_value[i])
	{
		if (arg_value[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
