/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:56:32 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/31 16:04:08 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data)
{
	t_env	*current_env;

	current_env = data->env_list;
	while (current_env)
	{
		if (current_env->show_in_env > 0)
			printf("%s\n", current_env->raw);
		current_env = current_env->next;
	}
}
