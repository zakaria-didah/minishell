#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>
#include "main.h"

void sigint_handler(int sig);
void sigquit_handler(int sig);
void	off_echoctl(void);
void	on_signal(void);

void	setup_signals_interactive(void);
void	setup_signals_default(void);
void	disable_echoctl(void);
void	default_signal(void);

#endif

