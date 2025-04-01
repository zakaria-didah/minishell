#include "signals.h"

void	sigint_handler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sigquit_handler(int sig)
{
	write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
	exit(131);
}
