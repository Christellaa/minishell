/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander_lens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:14:50 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/07 22:09:48 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_tools.h"

int		get_quoted_len(char *value, char quote);
int		get_len_until_quote(char *value);
int		env_var_len(char *var);

int	get_quoted_len(char *value, char quote)
{
	int	len;

	len = 1;
	while (value[len] && value[len] != quote)
		len++;
	return (len - 1);
}

int	get_len_until_quote(char *value)
{
	int	i;

	i = 0;
	while (value[i] && value[i] != SINGLE_QUOTE && value[i] != DOUBLE_QUOTE)
		i++;
	return (i);
}

char	*get_str_before_dollar(char *value, char *dollar_pos)
{
	int	len;

	len = dollar_pos - value;
	if (!len)
		return (ft_strdup(""));
	else
		return (ft_strndup(value, len));
}

char	*get_str_after_dollar(char *var)
{
	int	len;

	len = env_var_len(var);
	if (!var[len])
		return (ft_strdup(""));
	return (ft_strdup(var + len));
}

int	env_var_len(char *var)
{
	int	len;

	len = 0;
	if (var[len] == '?' || var[len] == '$')
		return (1);
	else if (ft_isdigit(var[len]))
		return (1);
	while (var[len])
	{
		if (var[len] != '_' && !ft_isalnum(var[len]))
			break ;
		len++;
	}
	return (len);
}
