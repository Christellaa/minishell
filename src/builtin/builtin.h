/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:56:15 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/09 17:14:06 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../includes/minishell.h"

// builtin
int		is_builtin(t_exec *exec_node);
void	check_builtin(t_data *data, t_exec *exec_node);
int		execute_builtin(int builtin, t_data *data, t_exec *exec_node);
// ft_exit
void	ft_exit(t_data *data, t_exec *exec_node, int std_in, int std_out);
// ft_cd
void	ft_cd(t_data *data, t_exec *exec_node);
// ft_pwd
void	ft_pwd(t_data *data, t_exec *exec_node);
// ft_env
void	ft_env(t_data *data, t_exec *exec_node);
// ft_export
void	ft_export(t_data *data, t_exec *exec_node);
int		check_and_replace_env_pair(t_env *new_node, t_env **list);
// ft_export_utils
t_env	*insertion_sort(t_env *sorted_list, t_env *new_node);
int		is_key_valid(char *value, t_data *data);
void	replace_env_pair(t_env *current_env, t_env *new_node);
// ft_unset
void	ft_unset(t_data *data, t_exec *exec_node);
// ft_echo
void	ft_echo(t_exec *exec_node);

#endif
