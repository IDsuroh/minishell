/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:52:20 by suroh             #+#    #+#             */
/*   Updated: 2025/03/31 01:17:44 by suroh            ###   ########.fr       */
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
	g_signal = 0;
}

void	signalhandler_execution(int signum)
{
	g_signal = signum;
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
