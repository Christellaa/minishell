/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:56:15 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/07 22:04:37 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../includes/minishell.h"

// builtin.c
int		is_builtin(t_exec *exec_node);
void	check_builtin(t_data *data, t_exec *exec_node);
int		execute_builtin(int builtin, t_data *data, t_exec *exec_node,
			int save_in, int save_out);
// ft_exit.c
void	ft_exit(t_data *data, t_exec *exec_node, int save_in, int save_out);
// ft_cd.c
void	ft_cd(t_data *data, t_exec *exec_node);
// ft_pwd.c
void	ft_pwd(t_data *data, t_exec *exec_node);
// ft_env.c
void	ft_env(t_data *data, t_exec *exec_node);
// ft_export.c
void	ft_export(t_data *data, t_exec *exec_node);
int		replace_existing_env_pair(t_env *new_node, t_env **list);
// ft_export_utils.c
t_env	*insertion_sort(t_env *sorted_list, t_env *new_node);
int		is_key_valid(char *value, t_data *data);
// ft_unset.c
void	ft_unset(t_data *data, t_exec *exec_node);
// ft_echo.c
void	ft_echo(t_exec *exec_node);

#endif
