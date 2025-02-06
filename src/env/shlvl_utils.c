/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:16:11 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 13:04:16 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	get_shlvl_number(char *shlvl_value)
{
	int	new_value;

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

int	get_buffer_count(int fd)
{
	int		count;
	char	buffer[10];
	int		bytes_read;

	count = 0;
	while (count < 10)
		buffer[count++] = 0;
	count = 0;
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read < 0)
		return (perror(FIRST_RUN_FILE), -1);
	buffer[bytes_read] = '\0';
	count = ft_atoi(buffer);
	return (count);
}
