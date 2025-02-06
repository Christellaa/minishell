/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:46:02 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/06 18:26:58 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_pwd(t_data *data, t_exec *exec_node)
{
	char	*pwd;
	t_arg	*arg;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		data->exit_code = 1;
		return ;
	}
	if (exec_node->arg_list->next)
	{
		arg = exec_node->arg_list->next;
		if (arg->value[0] == '-')
		{
			ft_dprintf(STDERR_FILENO, "pwd: %s: invalid option\n", arg->value);
			data->exit_code = 2;
			free(pwd);
			return ;
		}
	}
	printf("%s\n", pwd);
	free(pwd);
	return ;
}
