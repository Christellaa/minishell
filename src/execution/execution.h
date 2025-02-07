/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:16:27 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/07 21:50:57 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../../includes/minishell.h"

// child_process.c
int		execute_child_process(t_exec *exec_node, t_data *data);
// cmd_paths_utils.c
char	**get_and_split_paths(t_env *env_list);
int		is_absolute_path(char *cmd);
char	*get_relative_path(char *cmd, t_data *data, char **split_paths);
// execution.c
void	execute(t_data *data);
int		close_all_pipefds(t_data *data);
// heredoc_utils.c
int		handle_here_doc(t_data *data, t_exec *node);
char	*name_here_doc(char *value, int *i);
// redirs_utils.c
int		handle_redirs(t_data *data, t_exec *exec_node);
int		handle_files(t_data *data, t_exec *exec_node);

#endif
