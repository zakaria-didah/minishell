#include "main.h"

// char	*find_cmd(char *cmd)
// {
// 	int		i;
// 	char	*cmd_path;
// 	int		j;

// 	cmd_path = cmd;
// 	i = access(cmd, X_OK);
// 	j = 0;
// 	while (var->path[j] && access(cmd_path, X_OK))
// 	{
// 		cmd_path = ft_strjoin(var->path[j], cmd);
// 		j++;
// 	}
// 	if (!var->path[j])
// 		throw_error(ft_strjoin(cmd, ": command not found\n")), exit(FAILURE);
// 	return (cmd_path);
// }

// char	*join_args(char **args)
// {
// 	int		i;
// 	size_t	len;
// 	char	*arg;

// 	i = 0;
// 	len = 0;
// 	if (!args[i])
// 		return (NULL);
// 	while (args[i])
// 		len += ft_strlen(args[i++]) + 1;
// 	arg = ft_calloc(len);
// 	i = 0;
// 	while (args[i])
// 	{
// 		ft_strlcat(arg, args[i++], len);
// 		ft_strlcat(arg, " ", len);
// 	}
// 	return (arg);
// }
// // void	pipex(t_list *cmd_lst)
// // {

// // }

// int	exec(t_list *head)
// {
// 	pid_t child_pid;

// 	// if (ft_lstsize(head) > 1)
// 	// 	pipex(head);
// 	char *cmd = find_cmd(((t_cmd *)head->content)->args[0]);
// 	if (!cmd)
// 		return (127);
// 	child_pid = fork();
// 	if (child_pid < 0)
// 		exit(-1);
// 	var->curr_cmd = cmd;
// 	if (child_pid == 0)
// 	{
// 		redirect(head);
// 		execv(cmd, ((t_cmd *)head->content)->args);
// 		perror("shit happend\n");
// 		exit(1);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 	}
// 	return (SUCCESS);
// }
void	set_cmd_type(t_list *cmd_lst)
{
	char	*cmd;

	cmd = ((t_cmdlst *)cmd_lst->content)->args[0];
	if (!ft_strncmp(cmd, "echo", 5))
		((t_cmdlst *)cmd_lst->content)->type = ECHO;
	else if (!ft_strncmp(cmd, "cd", 3))
		((t_cmdlst *)cmd_lst->content)->type = CD;
	else if (!ft_strncmp(cmd, "pwd", 4))
		((t_cmdlst *)cmd_lst->content)->type = PWD;
	else if (!ft_strncmp(cmd, "EXPORT", 7))
		((t_cmdlst *)cmd_lst->content)->type = EXPORT;
	else if (!ft_strncmp(cmd, "UNSET", 6))
		((t_cmdlst *)cmd_lst->content)->type = UNSET;
	else if (!ft_strncmp(cmd, "env", 4))
		((t_cmdlst *)cmd_lst->content)->type = ENV;
	else if (!ft_strncmp(cmd, "exit", 5))
		((t_cmdlst *)cmd_lst->content)->type = EXIT;
	else
		((t_cmdlst *)cmd_lst->content)->type = NONE;
}

char	*get_path(char *cmd)
{
	char	**paths;

	if (access(cmd, F_OK))
	paths = var->path;
	while (paths)
	{
		
	}
}

int		execute_command(t_cmdlst cmd)
{
	pid_t	pid;
	int		output;
	int		input;

	pid = fork();
	if (pid == 0)
	{
		process_redirections(cmd.redirections, &input, &output);
		cmd.args[0] = get_path(cmd.args[0]);
		execve(cmd.args[0], cmd.args, var->env);
	}
	return (pid);
}

int		execute_builtin(t_cmdlst cmd)
{
	int	std_in;
	int	std_out;
	int	saved_stdin;
	int	saved_stdout;

	process_redirections(cmd.redirections, &std_in, &std_out);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	if (cmd.type == ECHO)
		ft_echo(cmd.args);
	else if (cmd.type == CD)
		ft_cd(cmd.args);
	else if (cmd.type == PWD)
		ft_pwd(cmd.args);
	else if (cmd.type == EXPORT)
		ft_export(cmd.args);
	else if (cmd.type = UNSET)
		ft_unset(cmd.args);
	else if (cmd.type == ENV)
		ft_env(cmd.args);
	else
		ft_exit(cmd.args);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	execute(t_list *cmd_lst)
{
	int	stat;

	if (ft_lstsize(cmd_lst) > 1)
		stat = pipeline(cmd_lst);
	else
	{
		set_cmd_type(cmd_lst);
		if (((t_cmdlst *)cmd_lst->content)->type == NONE)
			waitpid(execute_command(*(t_cmdlst *)cmd_lst->content), &stat, 0);
		else
			stat = execute_builtin(*(t_cmdlst *)cmd_lst->content);
	}
}
