/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:41:33 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/31 01:17:26 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signals_execution(void)
{
	signal(SIGINT, signalhandler_execution);
	signal(SIGQUIT, signalhandler_execution);
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
