/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:30:18 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/19 20:28:15 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigint_sigquit(int code)
{
	printf("\n");
	clear_rl_line();
	if (g_signal == 0)
		rl_redisplay();
	g_signal = 128 + code;
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_sigquit);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_child_signals(void)
{
	signal(SIGINT, sigint_sigquit);
	signal(SIGQUIT, sigint_sigquit);
}
