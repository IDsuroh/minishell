/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:52:20 by suroh             #+#    #+#             */
/*   Updated: 2025/03/13 18:24:52 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile int	g_signal = 0;

void	terminal_interrupt(t_pid_node *acpl)
{
	t_pid_node	*curr;

	curr = acpl;
	if (g_signal == SIGINT || g_signal == SIGQUIT)
	{
		while (curr)
		{
			kill(curr->pid, g_signal);
			curr = curr->next;
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
