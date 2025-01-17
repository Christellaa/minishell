/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:55:32 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/17 14:16:29 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*init_copy(t_token **cur_token)
{
	char	*copy;

	copy = ft_strdup((*cur_token)->value);
	if (!copy)
		return (print_error(6, NULL, NULL), NULL);
	free((*cur_token)->value);
	(*cur_token)->value = ft_strdup("");
	if (!(*cur_token)->value)
		return (print_error(6, NULL, NULL), NULL);
	return (copy);
}

char	*get_env_var(char *var_name, t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, var_name) == 0)
			return (tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

void	search_quote(char *quote, char *copy, int len)
{
	int	i;

	i = 0;
	while (copy[i] && i < len)
		*quote = has_quote(*quote, copy[i++]);
}

void	join_until_dollar(t_token **cur_token, char *copy, int len)
{
	char	*value;

	value = ft_substr(copy, 0, len);
	if (!value)
		return ;
	(*cur_token)->value = ft_strjoin_free_both((*cur_token)->value, value);
	if (!(*cur_token)->value)
		return (free(value));
}
