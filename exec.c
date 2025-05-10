#include "main.h"

char	**get_path(void)
{
	char	**path;
	char	*tmp;

	tmp = ft_getenv("PATH");
	if (!tmp)
		return (throw_error("PATH not found"), NULL);
	path = ft_split(tmp, ":");
	add_slash_to_path(path);
	return (path);
}

char	*find_cmd(char *cmd)
{
	int		i;
	char	*cmd_path;
	int		j;
	char	**path;

	cmd_path = cmd;
	path = get_path();
	if (!path || !cmd)
		return NULL;
	j = 0;
    if (!cmd[0])
        return (NULL);
	while (path[j] && access(cmd_path, X_OK))
	{
		cmd_path = ft_strjoin(path[j], cmd);
		j++;
	}
	if (!path[j])
	{
		throw_error(ft_strjoin(cmd, ": command not found"));
		return (NULL);
	}
	return (cmd_path);
}


pid_t	fork_cmd()
{
	pid_t	pid;
	int		stat;
	on_signal();
	pid = fork();
	// sleep(10);
	if (pid == -1)
		return (throw_error("fork failed\n"), exit(-1), -1);
		// setup_signals_default();
	return (pid);
}


int	exec_child(char **args)
{
	char *path;
	if(!args[0]){
		exit( SUCCESS);
	}
	
	path = find_cmd(args[0]);

	if (!path)
	{
		exit(127);
	}

	execve(path, args, var->env);
	ft_putendl_fd("shit happend", 2);
	ft_free();
	exit(errno);
}

pid_t	exec_cmd(t_list *cmd)
{
	pid_t	pid;
	int		stat;
	char	*path;

	pid = fork_cmd();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if(redirect(cmd)<0)
            exit(ERROR);
		exec_child(((t_cmd *)cmd->content)->args);
	}
	else
		waitpid(pid, &var->exit_s, 0);
	return (var->exit_s = WEXITSTATUS(var->exit_s), pid);
}

void pipe_it(int prev_fd, t_list *head, int fd[2]){
    if (prev_fd != -1)
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    if (head->next)
    {
        close(fd[0]); 
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
    if (redirect(head)<0)
        exit(ERROR);
    if (!exec_builtin(head))
        exec_child(((t_cmd *)head->content)->args);
    else 
        exit(0);
}


int pipex(t_list *head)
{
	int		fd[2];
	int		prev_fd = -1;
	pid_t	pid;
    int i = 0;

	while (head)
	{
		if (head->next && pipe(fd) < 0)
			return (perror("pipe"), -1);
		pid = fork_cmd(head);
		if (pid < 0)
			return (var->exit_s = -1, -1);
		else if (pid == 0)
            pipe_it(prev_fd, head, fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (head->next)
		{
			close(fd[1]); 
			prev_fd = fd[0]; 
		}
		head = head->next;
        i++;
	}
    while (i--)
	    waitpid(-1, &var->exit_s, 0);
	return (var->exit_s = WEXITSTATUS(var->exit_s),0);
}


void	execute(t_list *cmd_lst)
{
	pid_t	pid;

	if (ft_lstsize(cmd_lst) > 1)
		pipex(cmd_lst);
	else
	{
		if (!exec_builtin(cmd_lst))
		{
			pid = exec_cmd(cmd_lst);
			if (pid < 0)
				; // handel exit here...
		}
	}
}
