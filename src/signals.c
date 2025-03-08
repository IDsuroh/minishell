/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:52:20 by suroh             #+#    #+#             */
/*   Updated: 2025/03/07 21:26:57 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile int	g_signal = 0;

void	terminal_interrupt(pid_t *children_pid)
{
	if (g_signal == SIGINT || g_signal == SIGQUIT)
	{
		while (children_pid)
		{
			kill(*children_pid, g_signal);
			++children_pid;
		}
	}
	if (g_signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_signal = 0;
}

void	signalhandler_interactive(int signum)
{
	if (signum == SIGINT)
		g_signal = signum;
}

void	init_signals_interactive(void)
{
	signal(SIGINT, signalhandler_interactive);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signals_subshell(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
