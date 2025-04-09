#include "signals.h"
#include "main.h"

// ctrl + c
void	sigint_handler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	
}


void	sigquit_handler(int sig)
{
	write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
	exit(131);
}
