/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:55:32 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/16 15:32:26 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*init_copy(t_token **cur_token)
{
	char	*copy;

	copy = ft_strdup((*cur_token)->value);
	free((*cur_token)->value);
	(*cur_token)->value = ft_strdup("");
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

char	search_quote(char quote, char *copy, int len)
{
	int	i;

	i = 0;
	while (copy[i] && i < len)
		quote = has_quote(quote, copy[i++]);
	return (quote);
}

void	join_until_dollar(t_token **cur_token, char *copy, int len)
{
	char	*value;

	value = ft_substr(copy, 0, len);
	(*cur_token)->value = ft_strjoin_free_both((*cur_token)->value, value);
}

void	split_token(char *expanded, t_token **cur_token, char *copy)
{
	char	**split;
	int		i;
	t_token	*next;
	t_token	*new_token;
	t_token	*last;

	split = ft_split(expanded, ' ');
	(*cur_token)->value = ft_strjoin_free_both((*cur_token)->value, split[0]);
	i = 0;
	next = (*cur_token)->next;
	last = *cur_token;
	while (split[++i])
	{
		new_token = create_token(ARG, split[i], ft_strlen(split[i]));
		last->next = new_token;
		last = new_token;
	}
	last->next = next;
	last->value = ft_strjoin_free_s1(last->value, copy);
	i = 0;
	while (split[++i])
		free(split[i]);
	free(split);
}
