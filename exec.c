#include "main.h"

char	*find_cmd(char *cmd)
{
	int		i;
	char	*cmd_path;
	int		j;

	cmd_path = cmd;
	i = access(cmd, X_OK);
	j = 0;
	while (var->path[j] && i != SUCCESS)
	{
		cmd_path = ft_strjoin(var->path[j], cmd);
		i = access(cmd_path, X_OK);
		j++;
	}
	if (i != SUCCESS)
	{
		throw_error(ft_strjoin(cmd, ": command not found\n"));
		return (NULL);
	}
	return (cmd_path);
}

char	*join_args(char **args)
{
	int		i;
	size_t	len;
	char	*arg;

	i = 0;
	len = 0;
	if (!args[i])
		return (NULL);
	while (args[i])
		len += ft_strlen(args[i++]) + 1;
	arg = ft_calloc(len);
	i = 0;
	while (args[i])
	{
		ft_strlcat(arg, args[i++], len);
		ft_strlcat(arg, " ", len);
	}
	return (arg);
}

int	exec(t_list *head)
{
	pid_t child_pid;
	char *cmd = find_cmd(((t_cmd *)head->content)->args[0]);
	if (!cmd)
		return (127);
	child_pid = fork();
	if (child_pid < 0)
		exit(-1);
	if (child_pid == 0)
	{
		var->curr_cmd = cmd;
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