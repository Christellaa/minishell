/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:08:01 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/10 14:17:44 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

char	*print_path_error(char *cmd, t_data *data)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) != -1 && S_ISDIR(path_stat.st_mode))
		return (ft_dprintf(STDERR_FILENO, "%s: is a directory\n", cmd),
			ft_strdup(""));
	if (ft_strncmp(cmd, "./", 2) == 0 && access(cmd, F_OK) == 0)
		return (print_error(7, cmd, data), ft_strdup(""));
	else if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0)
		print_error(9, cmd, data);
	else
		print_error(8, cmd, data);
	return (NULL);
}

char	**convert_args_list_to_tab(t_arg *arg_list)
{
	int		i;
	t_arg	*current_arg;
	char	**args_tab;

	i = 0;
	current_arg = arg_list;
	while (current_arg)
	{
		i++;
		current_arg = current_arg->next;
	}
	args_tab = malloc((i + 1) * sizeof(char *));
	if (!args_tab)
		return (NULL);
	i = 0;
	current_arg = arg_list;
	while (current_arg)
	{
		args_tab[i++] = current_arg->value;
		current_arg = current_arg->next;
	}
	args_tab[i] = NULL;
	return (args_tab);
}

char	**convert_env_list_to_tab(t_env *env_list)
{
	int		i;
	t_env	*current_env;
	char	**env_tab;

	i = 0;
	current_env = env_list;
	while (current_env)
	{
		i++;
		current_env = current_env->next;
	}
	env_tab = malloc((i + 1) * sizeof(char *));
	if (!env_tab)
		return (NULL);
	i = 0;
	current_env = env_list;
	while (current_env)
	{
		env_tab[i++] = current_env->raw;
		current_env = current_env->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

void	dup_and_close_files(int std_in, int std_out, int to_dup, t_data *data)
{
	if (to_dup == 1)
	{
		if (dup2(std_in, STDIN_FILENO) == -1 \
		|| dup2(std_out, STDOUT_FILENO) == -1)
			print_error(4, "Dup", data);
	}
	close(std_in);
	close(std_out);
}
