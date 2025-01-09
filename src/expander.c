/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:03:43 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/09 21:08:51 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	replace_var_name(char *start, t_data *data, char **expanded)
{
	char	*var_name;
	char	*env_value;

	if (*(start + 1) == '?')
	{
		*expanded = ft_itoa(data->exit_code);
		return (1);
	}
	var_name = ft_strndup(start + 1, var_name_len(start + 1));
	env_value = get_env_var(var_name, data->env_list);
	free(var_name);
	if (!env_value)
		return (0);
	else // if no quote -> dup + trim it
		*expanded = ft_strdup(env_value);
	return (1);
}

void	expand_var(t_token **tmp, t_data *data)
{
	char	quote;
	char	*value;
	char	*expanded;
	char	*new_value;

	quote = '\0';
	value = (*tmp)->value;
	expanded = NULL;
	new_value = ft_strdup("");
	while (*value)
	{
		quote = has_quote(quote, *value);
		if (*value == '$' && quote != SINGLE_QUOTE && replace_var_name(value,
				data, &expanded))
		{
			new_value = ft_strjoin_free_both(new_value, expanded);
			value += var_name_len(value);
			continue ;
		}
		new_value = ft_strjoin_free_s1(new_value, ft_char_to_str(*value));
		value++;
	}
	free((*tmp)->value);
	(*tmp)->value = new_value;
}

void	remove_external_quotes(t_token **token)
{
	char	quote;
	char	*value;
	char	*new_value;

	quote = '\0';
	value = (*token)->value;
	new_value = ft_strdup("");
	while (*value)
	{
		if (*value == SINGLE_QUOTE || *value == DOUBLE_QUOTE)
			quote = *value;
		if (quote != *value)
			new_value = ft_strjoin_free_s1(new_value, ft_char_to_str(*value));
		value++;
	}
	free((*token)->value);
	(*token)->value = new_value;
}

void	expander(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		expand_var(&tmp, data);
		remove_external_quotes(&tmp);
		tmp = tmp->next;
	}
}
