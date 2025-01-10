/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:03:43 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/10 14:28:46 by carzhang         ###   ########.fr       */
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
	return (ft_strdup(""));
}

void	replace_var_name(char *start, t_data *data, char **expanded, char quote)
{
	char	*var_name;
	char	*env_value;

	if (*(start + 1) == '?')
	{
		*expanded = ft_itoa(data->exit_code);
		return ;
	}
	var_name = ft_strndup(start + 1, var_name_len(start + 1));
	env_value = get_env_var(var_name, data->env_list);
	free(var_name);
	if (!env_value)
		return ;
	else if (quote == '\0')
		*expanded = ft_strdup(epur_token_value(env_value));
	else
		*expanded = ft_strdup((env_value));
	return ;
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
		if (*value == '$' && quote != SINGLE_QUOTE)
		{
			replace_var_name(value, data, &expanded, quote);
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
		if ((*value == SINGLE_QUOTE || *value == DOUBLE_QUOTE) && quote == '\0')
			quote = *value;
		else if (quote != *value)
			new_value = ft_strjoin_free_s1(new_value, ft_char_to_str(*value));
		else if (quote == *value)
			quote = '\0';
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
