/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:03:43 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/08 19:29:43 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_var_name(char *start)
{
	char	*var_name;
	char	*end;

	start++;
	end = start;
	while (*end && !ft_isspace(*end) && *end != SINGLE_QUOTE
		&& *end != DOUBLE_QUOTE)
		end++;
	var_name = ft_substr(start, 0, end - start);
	return (var_name);
}

char	*ft_strjoin_three(char *start, char *middle, char *end)
{
	char	*new_value;
	int		len_start;
	int		len_middle;
	int		len_end;

	len_start = ft_strchr(start, '$') - start;
	len_middle = ft_strlen(middle);
	len_end = ft_strlen(end);
	new_value = malloc(len_start + len_middle + len_end + 1);
	if (!new_value)
		return (NULL);
	ft_strlcpy(new_value, start, len_start + 1);
	ft_strlcat(new_value, middle, len_start + len_middle + 1);
	if (end)
		ft_strlcat(new_value, end, len_start + len_middle + len_end + 1);
	return (new_value);
}

void	replace_var_name(t_env *env_list, t_token **tmp)
{
	t_env	*tmp_env;
	char	*var_name;
	char	*value;
	char	*start;

	tmp_env = env_list;
	start = ft_strchr((*tmp)->value, '$');
	var_name = extract_var_name(start);
	if (!var_name)
		return ;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, var_name) == 0)
		{
			value = ft_strjoin_three((*tmp)->value, tmp_env->value, start
					+ ft_strlen(var_name) + 1);
			free((*tmp)->value);
			(*tmp)->value = ft_strdup(value);
			break ;
		}
		tmp_env = tmp_env->next;
	}
	printf("value: %s\n", (*tmp)->value);
	free(value);
}

void	handle_env_var(t_token **tmp, t_data *data)
{
	if (ft_strchr((*tmp)->value, '$'))
	{
		if ((*tmp)->value[0] == SINGLE_QUOTE)
			return ;
		else
		{
			if ((*tmp)->value[1] == '?')
			{
				free((*tmp)->value);
				(*tmp)->value = ft_itoa(data->exit_code);
			}
			else
			{
				replace_var_name(data->env_list, tmp);
				if ((*tmp)->value[0] != DOUBLE_QUOTE)
					epur_token_value(tmp);
			}
		}
	}
}

void	remove_external_quotes(t_token **token)
{
	char	*value;

	if ((*token)->value[0] == SINGLE_QUOTE
		|| (*token)->value[0] == DOUBLE_QUOTE)
	{
		value = ft_substr((*token)->value, 1, ft_strlen((*token)->value) - 2);
		free((*token)->value);
		(*token)->value = ft_strdup(value);
	}
}

void	expander(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		handle_env_var(&tmp, data);
		remove_external_quotes(&tmp);
		tmp = tmp->next;
	}
}
