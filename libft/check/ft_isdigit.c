/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:23:23 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:36:28 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Checks for a digit (0 through 9)
** Returns nonzero if c is a digit, zero otherwise
*/

#include "../libft.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}
