#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>
#include "main.h"

void sigint_handler(int sig);
void sigquit_handler(int sig);

#endif

