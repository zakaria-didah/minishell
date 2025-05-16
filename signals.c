/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:26:05 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 22:22:30 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "signals.h"

void	sig_pipe(int sig)
{
	write(2, "we are fucked\n", 15);
}

void	signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_var.exit_s = 130;
}

void	default_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, sig_pipe);
}

void	sig_heredoc(int sig)
{
	(void)sig;
	g_var.hdoc = 130;
	g_var.exit_s = 130;
	close(STDIN_FILENO);
}
