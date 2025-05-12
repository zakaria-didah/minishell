#include "main.h"
#include "signals.h"

void	signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	var->exit_s = 130;
}

void	default_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	off_echoctl(void)
{
	struct termios	new_term;

	tcgetattr(STDOUT_FILENO, &new_term);
	new_term.c_lflag &= (~ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &new_term);
}
