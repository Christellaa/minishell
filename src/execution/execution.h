/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:16:27 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 13:09:04 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../../includes/minishell.h"

// child_process.c
char	**convert_args_list_to_tab(t_arg *arg_list);
char	**convert_env_list_to_tab(t_env *env_list);
char	*get_cmd_path(t_arg *arg_list, t_data *data);
int		execute_child_process(t_exec *exec_node, t_data *data);
// cmd_paths_utils.c
char	**get_and_split_paths(t_env *env_list);
int		is_absolute_path(char *cmd);
char	*get_relative_path(char *cmd, t_data *data, char **split_paths);
// execution.c
int		is_builtin(t_exec *exec_node);
int		create_pipes(t_data *data, t_exec *head_exec_list);
int		close_all_pipefds(t_data *data);
int		wait_all_pids(t_exec *head_exec_list);
void	execute(t_data *data);
// heredoc_utils.c
char	*name_here_doc(char *value, int *i);
void	write_in_heredoc(const char *delimiter, int fd);
int		handle_here_doc(t_data *data, t_exec *node);
int		write_mode_here_doc(t_files *file, int *i, t_data *data);
// redirs_utils.c
int		handle_redirs(t_data *data, t_exec *exec_node);
int		handle_files(t_data *data, t_exec *exec_node);

#endif
