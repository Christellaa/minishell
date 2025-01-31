/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylini <cylini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:51:04 by cylini            #+#    #+#             */
/*   Updated: 2025/01/31 23:18:36 by cylini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cd_args(t_exec *exec_node)
{
	t_arg	*args;

	args = exec_node->arg_list;
	args = args->next;
	if (!args)
		return (1);
	else if (args && !args->next)
		return (2);
	ft_dprintf(STDERR_FILENO, "%s: too many arguments\n",
		exec_node->arg_list->value);
	return (0);
}
int	update_pwd(t_data *data, char *old_pwd_value)
{
	char	*current_cwd;
	char	*old_pwd;
	char	*pwd;
	char	*pwd_path;
	char	*old_pwd_path;

	current_cwd = getcwd(NULL, 0);
	old_pwd = get_env_var("OLDPWD", data->env_list);
	pwd = get_env_var("PWD", data->env_list);
	if (pwd && current_cwd)
	{
		pwd_path = ft_strjoin("PWD=", current_cwd);
		if (!pwd_path)
			return (free(current_cwd), print_error(0, NULL, data), 0);
		free(pwd_path);
	}
	if (old_pwd && old_pwd_value)
	{
		old_pwd_path = ft_strjoin("OLDPWD=", old_pwd_value);
		if (!old_pwd_path)
			return (free(current_cwd), print_error(0, NULL, data), 0);
		free(old_pwd_path);
	}
	free(current_cwd);
	return (1);
}

int	ft_cd(t_data *data, t_exec *exec_node)
{
	char	*current_path;
	int		arg_nb;
	t_arg	*args;
	char	*target_path;

	args = exec_node->arg_list;
	args = args->next;
	arg_nb = check_cd_args(exec_node);
	if (arg_nb == 0)
	{
		data->exit_code = 1;
		return (0);
	}
	current_path = getcwd(NULL, 0);
	if (!current_path)
		perror("recovery of current directory failed");
	if (arg_nb == 2)
	{
		target_path = args->value;
		printf("args->value : %s\n", args->value);
	}
	if (chdir(target_path) == -1)
	{
		perror("cd");
		free(current_path);
		data->exit_code = 1;
		return (0);
	}
	update_pwd(data, current_path);
	free(current_path);
	return (1);
}

/* home = data->env_list;
if (arg_nb == 1 || ft_strcmp(args->value, "--") && (home && home->value))
{
	if (chdir(home->value) == -1)
	{
		err = errno;
		if (err = ENOENT)
		{
			free(current_path);
			ft_dprintf(STDERR_FILENO, "cd: %s: No such file or directory\n",
				home->value);
			return (1);
		}
	}
	return (1);
}
else if (arg_nb == 1 || ft_strcmp(args->value, "--") && !home)
	return (free(current_path), perror("cd : HOME not set\n"), 1); */