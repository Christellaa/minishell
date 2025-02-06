/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:09:26 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 16:30:07 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		is_newline(t_arg *arg);

void	ft_echo(t_exec *exec_node)
{
	t_arg	*arg;
	int		has_newline;

	arg = exec_node->arg_list->next;
	has_newline = 1;
	if (!arg)
	{
		printf("\n");
		return ;
	}
	while (is_newline(arg))
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

int	is_newline(t_arg *arg)
{
	int		i;
	char	*arg_value;

	i = 0;
	if (!arg)
		return (0);
	arg_value = arg->value;
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
