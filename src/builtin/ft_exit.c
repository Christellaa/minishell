/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:02:09 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/06 12:51:02 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"
#include "builtin.h"

int		check_exit_args(t_exec *exec_node);
int		get_exit_number(t_exec *exec_node);
int		is_number(char *exit_number);

void	ft_exit(t_data *data, t_exec *exec_node, int save_in, int save_out)
{
	int	exit_nb;

	printf("exit\n");
	if (!check_exit_args(exec_node))
	{
		data->exit_code = 1;
		return ;
	}
	exit_nb = get_exit_number(exec_node);
	if (save_in != -1)
		close(save_in);
	if (save_out != -1)
		close(save_out);
	close_all_pipefds(data);
	if (data->exec_list->next)
		cleanup(data, 2);
	else
		cleanup(data, 1);
	exit(exit_nb);
}

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

int	get_exit_number(t_exec *exec_node)
{
	t_arg		*arg;
	long long	code;
	char		*endptr;

	arg = exec_node->arg_list->next;
	if (!arg)
		return (0);
	if (!is_number(arg->value))
	{
		ft_dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			arg->value);
		return (2);
	}
	code = ft_strtoll(arg->value, &endptr, 10);
	if (errno == ERANGE)
	{
		ft_dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			arg->value);
		return (2);
	}
	code = code % 256;
	return (code);
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
