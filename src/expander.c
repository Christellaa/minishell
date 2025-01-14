/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:53:48 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/14 16:57:02 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_expandable(t_token *token_list, t_token *cur_token, int flag)
{
	t_token	*prev;
	t_token	*tmp;

	prev = token_list;
	tmp = cur_token;
	if (token_list != cur_token)
		prev = get_prev_token(token_list, tmp);
	if (flag == 1 && prev->type != INFILE && prev->type != HEREDOC
		&& prev->type != TRUNC && prev->type != APPEND)
		return (1);
	return (0);
}

char	*expand(char *pos, t_data *data, int *to_split, char quote)
{
	char	*var_name;
	char	*env_value;
	char	*value;

	if (quote == SINGLE_QUOTE)
		return (ft_strndup(pos - 1, var_name_len(pos) + 1));
	else if (*pos == '$' || ft_isspace(*pos) || *pos == '\0'
		|| *pos == SINGLE_QUOTE || *pos == DOUBLE_QUOTE)
		return (ft_strdup("$"));
	else if (*pos == '?')
		return (ft_itoa(data->exit_code));
	var_name = ft_strndup(pos, var_name_len(pos));
	env_value = get_env_var(var_name, data->env_list);
	free(var_name);
	if (!env_value)
		return (NULL);
	value = ft_strdup(env_value);
	if (ft_strchr(value, ' '))
		*to_split = 1;
	return (value);
}

void	expand_var(t_token **token, t_data *data, char *quote)
{
	char	*copy;
	char	*pos;
	char	*expanded;
	int		to_split;

	copy = init_copy(token);
	while (ft_strchr(copy, '$'))
	{
		expanded = NULL;
		to_split = 0;
		pos = ft_strchr(copy, '$');
		*quote = search_quote(*quote, copy, pos - copy);
		join_until_dollar(token, copy, pos - copy);
		expanded = expand(pos + 1, data, &to_split, *quote);
		copy = pos + 1 + var_name_len((pos + 1));
		if (to_split == 1 && *quote == '\0' && is_expandable(data->token_list,
				*token, 1))
			return (split_token(expanded, token, copy), free(expanded));
		if (expanded)
			(*token)->value = ft_strjoin_free_both((*token)->value, expanded);
	}
	if (*copy != '\0')
		(*token)->value = ft_strjoin_free_s1((*token)->value, copy);
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
	t_token	*prev;
	char	quote;

	tmp = data->token_list;
	prev = data->token_list;
	quote = '\0';
	while (tmp)
	{
		if (prev != data->token_list)
			prev = get_prev_token(prev, tmp);
		if (prev->type != HEREDOC)
			expand_var(&tmp, data, &quote);
		remove_external_quotes(&tmp);
		tmp = tmp->next;
	}
	delete_empty_tokens(&data->token_list);
}
