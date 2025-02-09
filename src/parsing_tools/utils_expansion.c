/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:17:55 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/09 17:03:01 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_tools.h"

char	*expand_var(char *var, t_data *data, char quote);
char	*handle_exit_status(char *var_name, t_data *data);
char	*fetch_env_value(char *value, t_env *list);

char	*handle_var_expansion(t_token *token, char *dollar_pos, t_data *data)
{
	char	*before;
	char	*var_value;
	char	*after;
	char	*new;

	before = get_str_before_dollar(token->value, dollar_pos);
	if (!before)
		return (print_error(0, NULL, data), NULL);
	var_value = expand_var(dollar_pos + 1, data, token->quote);
	if (!var_value)
		return (free(before), print_error(0, NULL, data), NULL);
	after = get_str_after_dollar(dollar_pos + 1);
	if (!after)
		return (free(before), free(var_value), print_error(0, NULL, data),
			NULL);
	new = ft_strjoin(before, var_value);
	if (!new)
		return (free(before), free(var_value), free(after), (NULL));
	new = ft_strjoin_free_s1(new, after);
	if (!new)
		return (free(before), free(var_value), free(after), NULL);
	return (free(before), free(var_value), free(after), new);
}

char	*expand_var(char *var, t_data *data, char quote)
{
	int		len;
	char	*var_name;
	char	*env_value;

	len = env_var_len(var);
	var_name = strndup(var, len);
	if (!var_name)
		return (NULL);
	if (!ft_strcmp(var_name, "?"))
		return (handle_exit_status(var_name, data));
	else if (!ft_strcmp(var_name, "$"))
		return (handle_pid(data));
	env_value = fetch_env_value(var_name, data->env_list);
	free(var_name);
	if (!env_value)
		return (ft_strdup(""));
	if (quote == '\0')
		return (ft_strepur(env_value));
	return (ft_strdup(env_value));
}

char	*handle_exit_status(char *var_name, t_data *data)
{
	if (g_signal != 0)
		data->exit_code = g_signal;
	free(var_name);
	var_name = ft_itoa(data->exit_code);
	return (var_name);
}

char	*fetch_env_value(char *value, t_env *list)
{
	t_env	*env;

	env = list;
	while (env)
	{
		if (!ft_strcmp(value, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
