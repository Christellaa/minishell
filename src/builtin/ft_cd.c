/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:51:04 by cylini            #+#    #+#             */
/*   Updated: 2025/02/06 14:53:08 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "builtin.h"

int		check_cd_args(t_data *data, t_arg *args);
void	update_pwd(t_data *data, char *old_pwd_value);
void	replace_and_add_current_pwd(char *current_pwd, t_data *data);

void	ft_cd(t_data *data, t_exec *exec_node)
{
	char	*current_path;
	t_arg	*args;

	args = exec_node->arg_list->next;
	if (check_cd_args(data, args))
		return ;
	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		perror("getcwd");
		data->exit_code = 1;
		return ;
	}
	if (chdir(args->value) == -1)
	{
		perror("cd");
		free(current_path);
		data->exit_code = 1;
		return ;
	}
	update_pwd(data, current_path);
	free(current_path);
}

int	check_cd_args(t_data *data, t_arg *args)
{
	if (!args || args->next)
	{
		data->exit_code = 1;
		if (!args)
			ft_dprintf(STDERR_FILENO, "cd: not enough argument\n");
		else
			ft_dprintf(STDERR_FILENO, "cd: too many arguments\n");
		return (1);
	}
	return (0);
}

void	update_pwd(t_data *data, char *old_pwd_value)
{
	char	*current_cwd;
	char	*pwd_path;
	char	*old_pwd_path;

	current_cwd = getcwd(NULL, 0);
	if (current_cwd)
	{
		pwd_path = ft_strjoin("PWD=", current_cwd);
		if (!pwd_path)
			return (free(current_cwd), print_error(0, NULL, data));
		replace_and_add_current_pwd(pwd_path, data);
	}
	if (old_pwd_value)
	{
		old_pwd_path = ft_strjoin("OLDPWD=", old_pwd_value);
		if (!old_pwd_path)
			return (free(current_cwd), print_error(0, NULL, data));
		replace_and_add_current_pwd(old_pwd_path, data);
	}
	free(current_cwd);
}

void	replace_and_add_current_pwd(char *current_pwd, t_data *data)
{
	t_env	*new_env_pair;

	new_env_pair = get_env_raw(current_pwd);
	if (!new_env_pair)
		return (print_error(0, NULL, data));
	if (!replace_existing_env_pair(new_env_pair, &data->env_list))
		add_env_node_to_list(&data->env_list, new_env_pair);
}
