#include "minishell.h"

void	signalhandler(int signum)
{
	g_signal = signum;
}

void	init_signals(void)
{
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
}
