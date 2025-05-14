#include "main.h"
#include "signals.h"

void	signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_var->exit_s = 130;
}

void	default_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_heredoc(int sig)
{
	(void)sig;
	g_var->hdoc = 130;
	g_var->exit_s = 130;
	close(STDIN_FILENO);
}
