/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:53:48 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/28 12:19:02 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		expand_current_token(t_token **token, t_data *data, char quote);
int		can_expand_token(t_token *prev_token, t_token *current_token,
			t_data *data, char quote);
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
		if (!can_expand_token(prev_token, current_token, data, quote))
			return (0);
		if (!remove_external_quotes(&current_token, data))
			return (0);
		current_token = current_token->next;
	}
	delete_empty_tokens(&data->token_list);
	return (1);
}

int	can_expand_token(t_token *prev_token, t_token *current_token, t_data *data,
		char quote)
{
	int	code;

	code = 0;
	if (prev_token->type != HEREDOC)
	{
		code = expand_current_token(&current_token, data, quote);
		if (code > 0)
			return (0);
		if (!(current_token)->value || code == -1)
			return (print_error(0, NULL, NULL, data), 0);
	}
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
		return (print_error(0, NULL, NULL, data));
	copy_tmp = copy;
	while (ft_strchr(copy, '$'))
	{
		to_split = 0;
		pos = search_quote_and_join_until_dollar(pos, &copy, &quote, token);
		if (!pos)
			return (print_error(0, NULL, NULL, data));
		expanded = handle_expansion(pos + 1, data, &to_split, quote);
		if (can_split_token(data->token_list, *token, to_split, quote))
			return (split_token(expanded, token, copy, copy_tmp));
		(*token)->value = ft_strjoin_free_both((*token)->value, expanded);
		if (!(*token)->value)
			return (free(copy_tmp), print_error(0, NULL, NULL, data));
	}
	(*token)->value = ft_strjoin_free_s1((*token)->value, copy, copy_tmp);
	return (0);
}

char	*search_quote_and_join_until_dollar(char *pos, char **copy, char *quote,
		t_token **token)
{
	pos = ft_strchr(*copy, '$');
	search_quote(quote, *copy, pos - *copy);
	join_until_dollar(token, *copy, pos - *copy);
	if (!(*token)->value)
		return (NULL);
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
		return (print_error(0, NULL, NULL, data), NULL);
	return (var_value);
}
