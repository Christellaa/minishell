/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:13:06 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 12:14:05 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../includes/minishell.h"

// env.c
t_env	*get_env_raw(char *current_env_pair);
t_env	*create_env_node(char *raw, char *key, char *value, int is_exported);
void	add_env_node_to_list(t_env **env_list, t_env *new_env);
int		get_env_list(t_data *data, char **envp);
// env2.c
int		create_env_list(t_data *data);
// shlvl.c
int		update_shlvl(t_env *env_list, t_data *data);
void	handle_exit_shlvl(void);
// shlvl_utils.c
int		get_shlvl_number(char *shlvl_value);
int		replace_shlvl_number(int value_nb, t_env *current_env, t_data *data);
int		get_buffer_count(int fd);

#endif
