#include "../main.h"

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

	while (cmd_lst)
	{
		ft_putendl_fd()
		cmd = ((t_cmd *)cmd_lst->content)->args[0];
		if (!ft_strncmp(cmd, "echo", 5))
			((t_cmd *)cmd_lst->content)->type = ECHO;
		else if (!ft_strncmp(cmd, "cd", 3))
			((t_cmd *)cmd_lst->content)->type = CD;
		else if (!ft_strncmp(cmd, "pwd", 4))
			((t_cmd *)cmd_lst->content)->type = PWD;
		else if (!ft_strncmp(cmd, "EXPORT", 7))
			((t_cmd *)cmd_lst->content)->type = EXPORT;
		else if (!ft_strncmp(cmd, "UNSET", 6))
			((t_cmd *)cmd_lst->content)->type = UNSET;
		else if (!ft_strncmp(cmd, "env", 4))
			((t_cmd *)cmd_lst->content)->type = ENV;
		else if (!ft_strncmp(cmd, "exit", 5))
			((t_cmd *)cmd_lst->content)->type = EXIT;
		else
			((t_cmd *)cmd_lst->content)->type = NONE;
		cmd_lst++;
	}
}

char	*get_path(char *cmd)
{
	char	**paths;
	char	*path;

	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK | X_OK))
			return (cmd);
		exit(FAILURE);
	}
	paths = ft_split(ft_getenv("PATH"), ":");
	if (!paths)
		exit(FAILURE);
	while (*paths)
	{
		path = ft_strjoin(ft_strjoin(*paths, "/"), cmd);
		if (!access(path, F_OK | X_OK))
			return (path);
		paths++;
	}
	exit(FAILURE);
}

int		execute_command(t_cmd cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		apply_redirections(cmd.rdc_lst);
		cmd.args[0] = get_path(cmd.args[0]);
		execve(cmd.args[0], cmd.args, var->env);
	}
	return (pid);
}

int	apply_redirections(t_list *redirections)
{
	int	input;
	int	output;
	int	fd;
	int hdc[2];

	while(redirections)
	{
		if (((t_red *)redirections->content)->type == RED_OUT || ((t_red *)redirections->content)->type == HDOC)
		{
			fd = open(((t_red *)redirections->content)->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(ft_strjoin("minishell: ", ((t_red *)redirections->content)->file));
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
		}
		else if (((t_red *)redirections->content)->type == RED_IN)
		{
			fd = open(((t_red *)redirections->content)->file, O_RDONLY);
			if (fd == -1)
			{
				perror(ft_strjoin("minishell: ", ((t_red *)redirections->content)->file));
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
		}
		else if (((t_red *)redirections->content)->type == APPEND)
		{
			fd = open(((t_red *)redirections->content)->file, O_WRONLY | O_CREAT |O_APPEND, 0644);
			if (fd == -1)
			{
				perror(ft_strjoin("minishell: ", ((t_red *)redirections->content)->file));
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
		}
		close(fd);
		redirections = redirections->next;
	}
	return (1);
}

void	init_pipeline(t_pipeline *data, t_list *cmd_lst)
{
	data->cmd_lst_size = ft_lstsize(cmd_lst);
	data->flag = 1;
}

int	wait_for_children(pid_t pid)
{
	pid_t	pid2;
	int		ex;
	int		status;

	while (1)
	{
		pid2 = wait(&status);
		if (pid2 == -1)
			break ;
		if (pid == pid2)
			ex = WEXITSTATUS(status);
	}
	return ex;
}

int	pipeline(t_list *cmd_lst)
{
	t_pipeline	data;
	int	stat;
	int	input;

	init_pipeline(&data, cmd_lst);
	input = STDIN_FILENO;
	while (data.flag <= data.cmd_lst_size)
	{
		if (data.flag != data.cmd_lst_size)
		{
			if (pipe(data.fds) == -1)
				return (-1);
		}
		data.pid = fork();
		if (data.pid == -1)
			return -1;
		if (!data.pid)
		{
			((t_cmd *)cmd_lst->content)->args[0] = get_path(((t_cmd *)cmd_lst->content)->args[0]);
			if (data.flag != 1)
			{
				dup2(input, STDIN_FILENO);
				close(input);
			}
			if (data.flag != data.cmd_lst_size)
			{
				dup2(data.fds[1], STDOUT_FILENO);
				close(data.fds[1]);
				close(data.fds[0]);
			}
			if (apply_redirections(((t_cmd *)cmd_lst->content)->rdc_lst) == -1)
				exit(EXIT_FAILURE);
			if (((t_cmd *)cmd_lst->content)->type == NONE)
			{
				execve(((t_cmd *)cmd_lst->content)->args[0], ((t_cmd *)cmd_lst->content)->args, var->env);
				perror("execve");
				exit(FAILURE);
			}
			else
			 	stat = execute_builtin(*(t_cmd *)cmd_lst->content);
			exit(stat);
		}
		if (data.flag != data.cmd_lst_size)
			close(data.fds[1]);
		if (data.flag != 1)
			close(input);
		input = data.fds[0];
		data.flag++;
		cmd_lst = cmd_lst->next;
	}
	stat = wait_for_children(data.pid);
	return (stat);
}

int	execute_builtin(t_cmd cmd)
{
	int	stat;

	if (cmd.type == ECHO)
		stat = echo(cmd.args + 1);
	else if (cmd.type == CD)
		stat = cd(cmd.args + 1);
	else if (cmd.type == PWD)
		stat = pwd(cmd.args + 1);
	else if (cmd.type == EXPORT)
		stat = export(cmd.args + 1);
	else if (cmd.type == UNSET)
		stat = unset(cmd.args + 1);
	else if (cmd.type == ENV)
		stat = env(cmd.args + 1);
	else
		stat = ft_exit(cmd.args + 1);
	return (stat);
}

void	exec(t_list *cmd_lst)
{
	int	stat;
	int	input;
	int	output;

	set_cmd_type(cmd_lst);
	if (ft_lstsize(cmd_lst) > 1 || ((t_cmd *)cmd_lst->content)->type == NONE)
		var->exit_s = pipeline(cmd_lst);
	else
	{
		if ((*(t_cmd *)cmd_lst->content).rdc_lst != NULL)
		{
			input = dup(0);
			output = dup(1);
			apply_redirections((*(t_cmd *)cmd_lst->content).rdc_lst);
		}
		var->exit_s = execute_builtin(*(t_cmd *)cmd_lst->content);
		if ((*(t_cmd *)cmd_lst->content).rdc_lst != NULL)
		{
			dup2(input, 0);
			dup2(output, 1);
			close(input);
			close(output);
		}
	}
}
