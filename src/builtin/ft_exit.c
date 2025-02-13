/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:02:09 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/13 15:52:58 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"
#include "builtin.h"

int		check_exit_args(t_exec *exec_node);
void	quit_ft_exit(t_data *data, int std_in, int std_out, int exit_nb);
int		get_exit_number(t_exec *exec_node, t_data *data);
int		is_number(char *exit_number);

void	ft_exit(t_data *data, t_exec *exec_node, int std_in, int std_out)
{
	int	exit_nb;

	printf("exit\n");
	exit_nb = check_exit_args(exec_node);
	if (exit_nb != 0)
	{
		if (data->exec_list->next)
			quit_ft_exit(data, std_in, std_out, exit_nb);
		data->exit_code = exit_nb;
		return ;
	}
	exit_nb = get_exit_number(exec_node, data);
	quit_ft_exit(data, std_in, std_out, exit_nb);
}

int	check_exit_args(t_exec *exec_node)
{
	t_arg	*args;

	args = exec_node->arg_list->next;
	if (!args || (args && !args->next))
	{
		if (args && !is_number(args->value))
		{
			ft_dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
				args->value);
			return (2);
		}
		return (0);
	}
	if (!is_number(args->value))
	{
		ft_dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			args->value);
		return (2);
	}
	ft_dprintf(STDERR_FILENO, "%s: too many arguments\n",
		exec_node->arg_list->value);
	return (1);
}

void	quit_ft_exit(t_data *data, int std_in, int std_out, int exit_nb)
{
	if (std_in != -1)
		close(std_in);
	if (std_out != -1)
		close(std_out);
	close_all_pipefds(data);
	if (data->exec_list->next)
		cleanup(data, 2);
	else
		cleanup(data, 1);
	exit(exit_nb);
}

int	get_exit_number(t_exec *exec_node, t_data *data)
{
	t_arg		*arg;
	long long	code;
	char		*endptr;

	arg = exec_node->arg_list->next;
	if (!arg)
		return (data->exit_code);
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

int	is_number(char *arg_value)
{
	if (!arg_value)
		return (0);
	if (*arg_value == '-' || *arg_value == '+' || ft_isdigit(*arg_value))
	{
		arg_value++;
		while (*arg_value)
		{
			if (!ft_isdigit(*arg_value))
				return (0);
			arg_value++;
		}
		return (1);
	}
	return (0);
}
