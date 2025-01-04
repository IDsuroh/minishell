#include "minishell.h"

<<<<<<< HEAD
=======
volatile int	g_signal = 0;

>>>>>>> 8809c1e (42push)
void	signalhandler(int signum)
{
	g_signal = signum;
}

void	init_signals(void)
{
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
}
