/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:01:47 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/02 17:06:23 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_file(t_tokens *token, char *input, int i)
{
	printf("%s", input);
	printf("%c", input[i]);
	(void)token;
}