#ifndef EXEC_H
# define EXEC_H
# include "main.h"
# include "parser.h"
# include "signals.h"



pid_t	exec_cmd(t_list *cmd);
int		exec_child(char **args);
void	execute(t_list *cmd_lst);
pid_t	fork_cmd(void);
bool	exec_builtin(t_list *cmdlst);
void	pipe_it(int prev_fd, t_list *head, int fd[2]);
int		check_next_pipe(t_list *head);
void	wait_for_it(pid_t pid, pid_t lastpid, int count);
int		pipex(t_list *head);
int	is_directory(const char *path);
char	*find_cmd(char *cmd);

#endif