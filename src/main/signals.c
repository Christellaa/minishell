/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:30:18 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 13:13:10 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_rl_line(void);
void	sigint(int code);
void	sigint_sigquit_child(int code);

void	handle_parent_signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_child_signals(void)
{
	signal(SIGINT, sigint_sigquit_child);
	signal(SIGQUIT, sigint_sigquit_child);
}

void	sigint(int code)
{
	printf("\n");
	clear_rl_line();
	rl_redisplay();
	g_signal = 128 + code;
}

void	sigint_sigquit_child(int code)
{
	printf("\n");
	clear_rl_line();
	g_signal = 128 + code;
}

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}
