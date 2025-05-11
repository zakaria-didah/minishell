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

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	is_executable(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (statbuf.st_mode & S_IXUSR) || (statbuf.st_mode & S_IXGRP)
		|| (statbuf.st_mode & S_IXOTH);
}

char	*find_cmd(char *cmd)
{
	int		i;
	char	*cmd_path;
	int		j;
	char	**path;

	cmd_path = cmd;
	if (access(cmd_path, F_OK))
	{
		path = get_path();
		if (!path || !cmd || !*cmd)
			return (NULL);
		j = 0;
		while (path[j] && access(cmd_path, X_OK))
		{
			cmd_path = ft_strjoin(path[j], cmd);
			j++;
		}
		if (!path[j])
			return (ft_strerror("command not found\n"), NULL);
	}
	if (is_directory(cmd_path))
		return (ft_strerror("is a directory\n"), NULL);
	if (!is_executable(cmd_path))
		return (ft_strerror("Permission denied\n"), NULL);
	return (cmd_path);
}

pid_t	fork_cmd(void)
{
	pid_t	pid;
	int		stat;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (throw_error("fork failed\n"), exit(-1), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	var->child = true;
	return (pid);
}

void	wait_for_it(pid_t pid, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		waitpid(pid, &var->exit_s, 0);
		if (WIFEXITED(var->exit_s))
			var->exit_s = WEXITSTATUS(var->exit_s);
		else if (WIFSIGNALED(var->exit_s))
			var->exit_s = WTERMSIG(var->exit_s) + 128;
		else if (WIFSTOPPED(var->exit_s))
			var->exit_s = WSTOPSIG(var->exit_s);
		else
			var->exit_s = ERROR;
		i++;
	}
	var->child = false;
	if (var->exit_s == 130)
		write(1, "\n", 1);
	else if (var->exit_s == 131)
		write(1, "Quit (core dumped)\n", 20);
}

int	exec_child(char **args)
{
	char	*path;

	if (!args[0])
	{
		exit(SUCCESS);
	}
	var->curr_cmd = args[0];
	path = find_cmd(args[0]);
	if (!path)
	{
		exit(127);
	}
	execve(path, args, var->env);
	ft_putendl_fd("shit happend", 2);
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
		if (redirect(cmd) < 0)
			exit(ERROR);
		exec_child(((t_cmd *)cmd->content)->args);
	}
	else
		wait_for_it(pid, 1);
	var->child = false;
	return (var->exit_s = WEXITSTATUS(var->exit_s), pid);
}

void	pipe_it(int prev_fd, t_list *head, int fd[2])
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
	if (redirect(head) < 0)
		exit(ERROR);
	if (!exec_builtin(head))
		exec_child(((t_cmd *)head->content)->args);
	else
		exit(0);
}

int	pipex(t_list *head)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid[ft_lstsize(head)];
	int		i;

	prev_fd = -1;
	i = 0;
	while (head)
	{
		if (head->next && pipe(fd) < 0)
			return (perror("pipe"), -1);
		pid[i] = fork_cmd();
		if (pid[i] < 0)
			return (var->exit_s = -1, -1);
		else if (pid[i] == 0)
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
	wait_for_it(-1, i);
	var->child = false;
	return (var->exit_s = WEXITSTATUS(var->exit_s), 0);
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
