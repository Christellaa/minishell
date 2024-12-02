/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:53:57 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/02 17:05:20 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isspace(int c)
{
	if ((char)c == ' ' || (char)c == '\f' || (char)c == '\t' || (char)c == '\n'
		|| (char)c == '\r' || (char)c == '\v')
		return (1);
	return (0);
}