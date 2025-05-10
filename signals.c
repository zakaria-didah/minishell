#include "signals.h"
#include "main.h"

void	signal_handler(int sig)
{
	int		status;

		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		var->exit_s = 130;


}


void handler(int sig)
{
	write(1,"\n",1);
}

void	on_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_DFL);
}

void	default_signal(void)
{
	// off_echoctl();
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
