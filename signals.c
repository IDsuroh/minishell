/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:52:20 by suroh             #+#    #+#             */
/*   Updated: 2025/01/04 15:52:24 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal = 0;

void	signalhandler(int signum)
{
	g_signal = signum;
}

void	init_signals(void)
{
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
}
