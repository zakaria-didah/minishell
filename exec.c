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
	// i = access(cmd, X_OK);
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

// void	pipex(t_list *cmd_lst)
// {

// }

pid_t	fork_cmd(t_list *cmd, char **path)
{
	pid_t	pid;
	int		stat;

	*path = find_cmd(((t_cmd *)cmd->content)->args[0]);
	if (!*path)
		return (-1);
	var->curr_cmd = ((t_cmd *)cmd->content)->args[0];
	((t_cmd *)cmd->content)->args[0] = *path;
	pid = fork();
	if (pid == -1)
		return (throw_error("fork failed\n"), exit(-1), -1);
	return (pid);
}
/*
int	exec(t_list *head)
{
	pid_t	child_pid;
	char	*cmd;

	// if (ft_lstsize(head) > 1)
	// 	pipex(head);
	cmd = find_cmd(((t_cmd *)head->content)->args[0]);
	if (!cmd)
		return (127);
	child_pid = fork();
	if (child_pid < 0)
		exit(-1);
	var->curr_cmd = cmd;
	if (child_pid == 0)
	{
		redirect(head);
		execv(cmd, ((t_cmd *)head->content)->args);
		perror("shit happend\n");
		exit(1);
	}
	else
	{
		wait(NULL);
	}
	return (SUCCESS);
}
*/

void	exec_child(char *path, char **args)
{
	execve(path, args, var->env);
	perror(strerror(errno));
	ft_putendl_fd("shit happend", 2);
	ft_free();
	exit(1);
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
