/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:01:36 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/03 18:01:09 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_first_run(t_data *data);
int		get_shlvl_number(char *shlvl_value);
int		replace_shlvl_number(int value_nb, t_env *current_env, t_data *data);

int	update_shlvl(t_env *env_list, t_data *data)
{
	t_env	*current_env;
	int		value_nb;
	int		run_number;

	current_env = env_list;
	run_number = is_first_run(data);
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

int	is_first_run(t_data *data)
{
	int		fd;
	char	buffer[10];
	int		count;

	fd = open(FIRST_RUN_FILE, O_CREAT | O_RDWR, 0644);
	if (fd == -1 && access(FIRST_RUN_FILE, F_OK) == 0)
		return (print_error(2, FIRST_RUN_FILE, data), -1);
	else if (fd == -1)
		return (print_error(1, FIRST_RUN_FILE, data), -1);
	count = 0;
	if (read(fd, buffer, sizeof(buffer) - 1) > 0)
		count = atoi(buffer);
	close(fd);
	fd = open(FIRST_RUN_FILE, O_WRONLY | O_TRUNC, 0644);
	if (fd == -1 && access(FIRST_RUN_FILE, F_OK) == 0)
		return (print_error(2, FIRST_RUN_FILE, data), -1);
	else if (fd == -1)
		return (print_error(1, FIRST_RUN_FILE, data), -1);
	if (count == 0)
		ft_dprintf(fd, "1");
	else
		ft_dprintf(fd, "%d", count + 1);
	close(fd);
	return (count == 0);
}

int	get_shlvl_number(char *shlvl_value)
{
	int	new_value;

	new_value = 0;
	new_value = ft_atoi(shlvl_value);
	if (new_value == 0 && ft_strcmp(shlvl_value, "0") != 0)
		new_value = 1;
	else
		new_value++;
	return (new_value);
}

int	replace_shlvl_number(int value_nb, t_env *current_env, t_data *data)
{
	char	*new_value;

	new_value = ft_itoa(value_nb);
	if (!new_value)
		return (print_error(0, NULL, data), 0);
	free(current_env->raw);
	free(current_env->value);
	current_env->raw = ft_strjoin("SHLVL=", new_value);
	current_env->value = new_value;
	if (!current_env->raw)
		return (print_error(0, NULL, data), 0);
	return (1);
}

void	handle_exit_shlvl(void)
{
	int		fd;
	char	buffer[10];
	int		count;

	count = 0;
	fd = open(FIRST_RUN_FILE, O_RDWR, 0644);
	if (fd < 0)
		return (perror(FIRST_RUN_FILE));
	if (read(fd, buffer, sizeof(buffer) - 1) > 0)
		count = ft_atoi(buffer);
	close(fd);
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
