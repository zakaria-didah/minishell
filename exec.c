#include "main.h"

char	**get_path(void)
{
	char	**path;
	char	*tmp;

	tmp = ft_getenv("PATH");
	if (!tmp)
		return (throw_error("PATH not found\n"), NULL);
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
	if (!path)
		return NULL;
	j = 0;
	while (path[j] && access(cmd_path, X_OK))
	{
		cmd_path = ft_strjoin(path[j], cmd);
		j++;
	}
	if (!path[j])
	{
		throw_error(ft_strjoin(cmd, ": command not found\n"));
		return (NULL);
	}
	return (cmd_path);
}


pid_t	fork_cmd(t_list *cmd, char **path)
{
	pid_t	pid;
	int		stat;
	
	pid = fork();
	if (pid == -1)
		return (throw_error("fork failed\n"), exit(-1), -1);
	if (pid == 0){
		*path = find_cmd(((t_cmd *)cmd->content)->args[0]);
		if (!*path)
			return (exit(127), -1);
		var->curr_cmd = ((t_cmd *)cmd->content)->args[0];
		((t_cmd *)cmd->content)->args[0] = *path;
	}
	return (pid);
}


void	exec_child(char *path, char **args)
{
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

	pid = fork_cmd(cmd, &path);
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		redirect(cmd);
		exec_child(path, ((t_cmd *)cmd->content)->args);
	}
	else
		waitpid(pid, &stat, 0);
	return (pid);
}


int pipex(t_list *head)
{
	int		fd[2];
	int		prev_fd = -1;
	pid_t	pid;
	size_t	i = 0;
	char *path;
	size_t	len = ft_lstsize(head);


	while (head)
	{
		if (head->next && pipe(fd) < 0)
			return (perror("pipe"), -1);

		pid = fork_cmd(head, &path);
		if (pid < 0)
			return (perror("fork"), -1);
		else if (pid == 0)
		{
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
			exec_child(path,((t_cmd *)head->content)->args);
		}

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
	while (i-- > 0)
		wait(NULL);
	return (0);
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
