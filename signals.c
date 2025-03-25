#include "signals.h"

void sigint_handler(int sig){
  write(STDOUT_FILENO, "\n", 1); // Write a newline
  rl_on_new_line();              // Tell readline to move to a new line
  rl_replace_line("", 0);        // Clear the current input line
  rl_redisplay(); 
  
}

void sigquit_handler(int sig){
  write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
  ft_exit(131);
}
