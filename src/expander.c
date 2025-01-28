/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:53:48 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/28 09:57:46 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		expand_current_token(t_token **token, t_data *data, char quote);
char	*search_quote_and_join_until_dollar(char *pos, char **copy, char *quote,
			t_token **token);
char	*handle_expansion(char *pos, t_data *data, int *to_split, char quote);
char	*fetch_env_value(char *pos, t_data *data, int *to_split);

int	expand_tokens(t_data *data)
{
	t_token	*current_token;
	t_token	*prev_token;
	char	quote;

	current_token = data->token_list;
	prev_token = data->token_list;
	while (current_token)
	{
		quote = '\0';
		if (prev_token != data->token_list)
			prev_token = get_prev_token(prev_token, current_token);
		if (prev_token->type != HEREDOC)
		{
			if (expand_current_token(&current_token, data, quote))
			{
				data->exit_code = 1;
				return (0);
			}
		}
		if (!remove_external_quotes(&current_token, data))
			return (0);
		current_token = current_token->next;
	}
	delete_empty_tokens(&data->token_list);
	return (1);
}

int	expand_current_token(t_token **token, t_data *data, char quote)
{
	char	*copy;
	char	*copy_tmp;
	char	*pos;
	char	*expanded;
	int		to_split;

	copy = init_copy(token);
	if (!copy)
		return (1);
	copy_tmp = copy;
	while (ft_strchr(copy, '$'))
	{
		to_split = 0;
		pos = search_quote_and_join_until_dollar(pos, &copy, &quote, token);
		expanded = handle_expansion(pos + 1, data, &to_split, quote);
		if (can_split_token(data->token_list, *token, to_split, quote))
			return (split_token(expanded, token, copy, copy_tmp));
		(*token)->value = ft_strjoin_free_both((*token)->value, expanded);
		if (!(*token)->value)
			return (free(copy_tmp), print_error(6, NULL, NULL));
	}
	(*token)->value = ft_strjoin_free_s1((*token)->value, copy, copy_tmp);
	if (!(*token)->value)
		return (print_error(6, NULL, NULL));
	return (0);
}

char	*search_quote_and_join_until_dollar(char *pos, char **copy, char *quote,
		t_token **token)
{
	pos = ft_strchr(*copy, '$');
	search_quote(quote, *copy, pos - *copy);
	join_until_dollar(token, *copy, pos - *copy);
	if (!(*token)->value)
		return (print_error(6, NULL, NULL), NULL);
	*copy = pos + 1 + var_name_len((pos + 1));
	return (pos);
}

char	*handle_expansion(char *pos, t_data *data, int *to_split, char quote)
{
	char	*var_value;

	if (*pos < 0)
		return (NULL);
	if (quote == SINGLE_QUOTE)
		var_value = ft_strndup(pos - 1, var_name_len(pos) + 1);
	else if (*pos == '$' || ft_isspace(*pos) || *pos == '\0')
		var_value = ft_strdup("$");
	else if (*pos == SINGLE_QUOTE || *pos == DOUBLE_QUOTE)
		return (NULL);
	else if (*pos == '?')
	{
		if (g_signal != 0)
		{
			data->exit_code = g_signal;
			g_signal = 0;
		}
		var_value = ft_itoa(data->exit_code);
	}
	else
		var_value = fetch_env_value(pos, data, to_split);
	if (!var_value)
		return (print_error(6, NULL, NULL), NULL);
	return (var_value);
}

char	*fetch_env_value(char *pos, t_data *data, int *to_split)
{
	char	*var_value;
	char	*env_value;

	var_value = ft_strndup(pos, var_name_len(pos));
	if (!var_value)
		return (print_error(6, NULL, NULL), NULL);
	env_value = get_env_var(var_value, data->env_list);
	free(var_value);
	if (!env_value)
		var_value = ft_strdup("");
	else
		var_value = ft_strdup(env_value);
	if (!var_value)
		return (print_error(6, NULL, NULL), NULL);
	if (ft_strchr(var_value, ' '))
		*to_split = 1;
	return (var_value);
}
