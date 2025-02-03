/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:51:04 by cylini            #+#    #+#             */
/*   Updated: 2025/02/03 17:58:25 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int	check_cd_args(t_exec *exec_node)
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
*/

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

int	check_cd_args(t_data *data, t_arg *args)
{
	if (!args || args->next)
	{
		data->exit_code = 1;
		if (!args)
		{
			ft_dprintf(STDERR_FILENO, "cd: not enough argument\n");
			return (1);
		}
		ft_dprintf(STDERR_FILENO, "%s: too many arguments\n", args->value);
		return (2);
	}
	return (0);
}

void	ft_cd(t_data *data, t_exec *exec_node)
{
	char	*current_path;
	t_arg	*args;

	args = exec_node->arg_list->next;
	if (check_cd_args(data, args))
		return ;
	if (!(current_path = getcwd(NULL, 0)))
	{
		print_error(4, "Getcwd", data);
		return ;
	}
	if (chdir(args->value) == -1)
	{
		if (errno == EACCES)
			ft_dprintf(STDERR_FILENO, "cd: %s: Permission denied\n", args->value);
		else
			ft_dprintf(STDERR_FILENO, "cd: %s: No such file or directory\n",
				args->value);
		free(current_path);
		data->exit_code = 1;
		return ;
	}
	update_pwd(data, current_path);
	free(current_path);
}

// perror("getcwd");
// data->exit_code = 1;
/* void	ft_cd(t_data *data, t_exec *exec_node)
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
		return ;
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
		return ;
	}
	update_pwd(data, current_path);
	free(current_path);
	return ;
} */
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