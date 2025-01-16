/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:53:48 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/16 15:31:36 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	can_split(t_token *token_list, t_token *cur_token, int to_split, char quote)
{
	t_token	*prev;
	t_token	*tmp;

	prev = token_list;
	tmp = cur_token;
	if (token_list != cur_token)
		prev = get_prev_token(token_list, tmp);
	if (to_split == 1 && quote == '\0' && prev->type != INFILE
		&& prev->type != TRUNC && prev->type != APPEND)
		return (1);
	return (0);
}

char	*expand(char *pos, t_data *data, int *to_split, char quote)
{
	char	*var_value;
	char	*env_value;

	if (quote == SINGLE_QUOTE)
		return (ft_strndup(pos - 1, var_name_len(pos) + 1));
	else if (*pos == '$' || ft_isspace(*pos) || *pos == '\0')
		return (ft_strdup("$"));
	else if (*pos == SINGLE_QUOTE || *pos == DOUBLE_QUOTE)
		return (NULL);
	else if (*pos == '?')
		return (ft_itoa(data->exit_code));
	var_value = ft_strndup(pos, var_name_len(pos));
	env_value = get_env_var(var_value, data->env_list);
	free(var_value);
	if (!env_value)
		return (NULL);
	var_value = ft_strdup(env_value);
	if (ft_strchr(var_value, ' '))
		*to_split = 1;
	return (var_value);
}

void	expand_var(t_token **token, t_data *data, char *quote)
{
	char	*copy;
	char	*tmp;
	char	*pos;
	char	*expanded;
	int		to_split;

	copy = init_copy(token);
	tmp = copy;
	while (ft_strchr(copy, '$'))
	{
		expanded = NULL;
		to_split = 0;
		pos = ft_strchr(copy, '$');
		*quote = search_quote(*quote, copy, pos - copy);
		join_until_dollar(token, copy, pos - copy);
		expanded = expand(pos + 1, data, &to_split, *quote);
		copy = pos + 1 + var_name_len((pos + 1));
		if (can_split(data->token_list, *token, to_split, *quote))
			return (split_token(expanded, token, copy), free(expanded),
				free(tmp));
		if (expanded)
			(*token)->value = ft_strjoin_free_both((*token)->value, expanded);
	}
	if (*copy != '\0')
		(*token)->value = ft_strjoin_free_s1((*token)->value, copy);
	free(tmp);
}

void	remove_external_quotes(t_token **token)
{
	char	quote;
	char	*value;
	char	*new_value;
	char	*str;

	quote = '\0';
	value = (*token)->value;
	new_value = ft_strdup("");
	while (*value)
	{
		if ((*value == SINGLE_QUOTE || *value == DOUBLE_QUOTE) && quote == '\0')
			quote = *value;
		else if (quote != *value)
		{
			str = ft_char_to_str(*value);
			new_value = ft_strjoin_free_both(new_value, str);
		}
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
