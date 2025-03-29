/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:52:20 by suroh             #+#    #+#             */
/*   Updated: 2025/03/29 20:40:53 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile int	g_signal = 0;

void	terminal_interrupt(t_almighty *mighty)
{
	t_pid_node	*curr;

	curr = mighty->acpl;
	if (g_signal == SIGINT || g_signal == SIGQUIT)
	{
		if (g_signal == SIGINT)
			mighty->exit_stat = 130;
		if (g_signal == SIGQUIT)
			mighty->exit_stat = 131;
		while (curr)
		{
			kill(curr->pid, g_signal);
			curr = curr->next;
		}
	}
}

void	signalhandler_interactive(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		g_signal = signum;
}

void	init_signals_execution(void)
{
	signal(SIGINT, signalhandler_interactive);
	signal(SIGQUIT, signalhandler_interactive);
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
