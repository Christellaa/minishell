/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:01:36 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/04 14:17:08 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_first_run(void);

int	update_shlvl(t_env *env_list, t_data *data)
{
	t_env	*current_env;
	int		value_nb;
	int		run_number;

	current_env = env_list;
	run_number = is_first_run();
	if (run_number == -1)
		return (0);
	else if (run_number)
		return (1);
	while (current_env)
	{
		if (ft_strcmp(current_env->key, "SHLVL") == 0)
		{
			value_nb = get_shlvl_number(current_env->value);
			if (!replace_shlvl_number(value_nb, current_env, data))
				return (0);
			return (1);
		}
		current_env = current_env->next;
	}
	return (1);
}

int	is_first_run(void)
{
	int	fd;
	int	count;

	fd = open(FIRST_RUN_FILE, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (perror(FIRST_RUN_FILE), -1);
	count = get_buffer_count(fd);
	if (count == -1)
		return (-1);
	fd = open(FIRST_RUN_FILE, O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(FIRST_RUN_FILE), -1);
	if (count == 0)
		ft_dprintf(fd, "1");
	else
		ft_dprintf(fd, "%d", count + 1);
	close(fd);
	return (count == 0);
}

void	handle_exit_shlvl(void)
{
	int	fd;
	int	count;

	fd = open(FIRST_RUN_FILE, O_RDWR, 0644);
	if (fd < 0)
		return (perror(FIRST_RUN_FILE));
	count = get_buffer_count(fd);
	if (count == -1)
		return ;
	if (count > 1)
	{
		fd = open(FIRST_RUN_FILE, O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(FIRST_RUN_FILE));
		ft_dprintf(fd, "%d", count - 1);
		close(fd);
	}
	else if (unlink(FIRST_RUN_FILE) < 0)
		return (perror(FIRST_RUN_FILE));
}
