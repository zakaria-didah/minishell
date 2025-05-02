#include "signals.h"
#include "main.h"

/*
void	sigint_handler(int sig)
{
	// if (var->hdoc == 1)
	// {
	// 	write(STDOUT_FILENO, "\n", 1);
	// 	exit(130);
	// }
	// else if (var->hdoc == 0)
	// 	write(STDOUT_FILENO, "\n", 1);
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
}*/


// void	signal_handler(int sig)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = waitpid(-1, &status, WNOHANG);
// 	if (pid == -1)
// 	{
// 		printf("\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	else
// 	{
// 		if (sig == SIGINT)
// 			printf("^C\n");
// 		if (sig == SIGQUIT)
// 			printf("^\\Quit:3\n");
// 	}
// }

// void	on_signal(void)
// {
// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, signal_handler);
// }

// void	default_signal(void)
// {
// 	off_echoctl();
// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }


// void	off_echoctl(void)
// {
// 	struct termios	new_term;

// 	tcgetattr(STDOUT_FILENO, &new_term);
// 	new_term.c_lflag &= (~ECHOCTL);
// 	tcsetattr(STDOUT_FILENO, TCSANOW, &new_term);
// }


#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	g_exit_status = 0;

static void	signal_handler(int sig)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (pid <= 0)
	{
		// Shell prompt – interactive mode
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_exit_status = 1;
		}
		else if (sig == SIGQUIT)
		{
			// Do nothingt
		}
	}
	else
	{
		// Child process
		if (sig == SIGINT)
			write(1, "^C\n", 3);
		else if (sig == SIGQUIT)
			write(1, "^\\Quit: 3\n", 10);
		g_exit_status = 128 + sig;
	}
}

void	setup_signals_interactive(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	setup_signals_default(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	disable_echoctl(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
