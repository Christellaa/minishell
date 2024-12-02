/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:41:36 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:36:55 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates an new array and store the substrs obtained from splitting the
** string s at each occurence of c
** Returns the array of strings obtained, or NULL if the allocation fails
*/

#include "../libft.h"

static void	*free_substr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static size_t	count_substrs(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*create_substr(char const *str, char sep)
{
	int		i;
	char	*substr;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	substr = malloc((i + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != sep)
	{
		substr[i] = str[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static char	**split_substrs(char const *s, char sep, char **arr, \
							size_t substr_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < substr_count)
	{
		while (s[j] && s[j] == sep)
			j++;
		if (s[j])
		{
			arr[i] = create_substr(s + j, sep);
			if (!arr[i])
			{
				free_substr(arr);
				return (NULL);
			}
			i++;
		}
		while (s[j] && s[j] != sep)
			j++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	substr_count;

	substr_count = count_substrs(s, c);
	arr = malloc((substr_count + 1) * sizeof(char *));
	if (!s || !arr)
		return (NULL);
	arr = split_substrs(s, c, arr, substr_count);
	return (arr);
}
