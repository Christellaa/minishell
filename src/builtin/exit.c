/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylini <cylini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:02:09 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/31 15:35:57 by cylini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_exit_args(t_exec *exec_node)
{
	t_arg	*args;

	args = exec_node->arg_list;
	args = args->next;
	if (!args || (args && !args->next))
		return (1);
	ft_dprintf(STDERR_FILENO, "%s: too many arguments\n",
		exec_node->arg_list->value);
	return (0);
}

int	is_number(char *exit_number)
{
	char	*nb;

	nb = ft_strdup(exit_number);
	if (*nb == '-' || *nb == '+' || ft_isdigit(*nb))
	{
		nb++;
		while (*nb)
		{
			if (!ft_isdigit(*nb))
				return (0);
			nb++;
		}
		return (1);
	}
	return (0);
}

int	get_exit_number(t_exec *exec_node)
{
	t_arg		*arg;
	long long	code;
	char		*endptr;

	arg = exec_node->arg_list;
	arg = arg->next;
	if (!arg)
		return (0);
	if (!is_number(arg->value))
	{
		ft_dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			arg->value);
		return (-1);
	}
	code = ft_strtoll(arg->value, &endptr, 10);
	if (errno == ERANGE)
	{
		ft_dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			arg->value);
		return (-1);
	}
	code = code % 256;
	return (code);
}

void	ft_exit(t_data *data, t_exec *exec_node)
{
	int	exit_nb;

	if (!check_exit_args(exec_node))
	{
		data->exit_code = 1;
		return ;
	}
	exit_nb = get_exit_number(exec_node);
	if (exit_nb == -1)
		return ;
	cleanup(data, 1);
	exit(exit_nb);
}
