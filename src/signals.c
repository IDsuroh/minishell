/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:52:20 by suroh             #+#    #+#             */
/*   Updated: 2025/01/04 23:45:00 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile int	g_signal = 0;

void	terminal_interrupt(void)
{
	if (g_signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 0;
	}
}

void	signalhandler(int signum)
{
	if (signum == SIGINT)
		g_signal = signum;
}

void	init_signals(void)
{
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
}
