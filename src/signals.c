/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:30:18 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/17 17:15:45 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigInt(int code)
{
	(void)code;
	printf("\nminishell$ ");
	rl_redisplay();
}

void	handle_signals(void)
{
	signal(SIGINT, sigInt);
	signal(SIGQUIT, SIG_IGN);
}
