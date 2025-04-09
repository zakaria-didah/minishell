#include "main.h"

t_var	*var = NULL;

int	ft_unset(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		unsetenv(args[i++]);
	}
	return (true);
}

int	ft_export(char **args)
{
	char	*value;
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i])
	{
		while (args[i][j] && args[i][j] != '=')
		{
			j++;
		}
		value = args[i] + j + 1;
		name = args[i];
		name[j] = '\0';
		setenv(name, value, 1);
		j = 0;
		i++;
	}
	ft_remove(args);
}


// int	ft_echo(char **args)
// {
// 	char	*str;
// 	int		i;
// 	int		j;
// 	char	*var;
// 	int		new_line;

// 	new_line = 0;
// 	i = 0;
// 	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
// 	{
// 		new_line = TRUE;
// 		i++;
// 	}
// 	while (args[i])
// 	{
// 		ft_putstr_fd(args[i++], STDOUT_FILENO);
// 		ft_putchar_fd(' ', STDOUT_FILENO);
// 	}
// 	if (!new_line)
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 	return (0);
// }

void	ft_error(char *s)
{
	size_t	len;
	char	prefix[len];

	len = ft_strlen(var->curr_cmd) + 3;
	ft_strlcpy(prefix, var->curr_cmd, len);
	ft_strlcat(prefix, ": ", len);
	ft_putstr_fd(prefix, STDERR_FILENO);
	if (s)
	{
		ft_putstr_fd(s, STDERR_FILENO);
	}
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

int	ft_cd(char **args)
{
	char	*path;
	char	*home;
	int		stat;

	stat = 0;
	if (ft_arrlen(args) > 1)
		return (ft_error(NULL), ERROR);
	if (args && args[0])
	{
		if (args[0][0] == '~')
		{
			home = getenv("HOME");
			path = ft_strjoin(home, args[0] + 1);
		}
		else if (args[0][0] == '-' && args[0][1] == '\0')
			path = var->oldpwd;
		else
			path = args[0];
	}
	else
		path = getenv("HOME");
	stat = chdir(path);
	if (stat != SUCCESS)
		return (ft_error(ft_strjoin(args[0], ": ")), ERROR);
}
/*to get a prompt with the current working dir.*/
char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	prompt = ft_strrchr(cwd, '/');
	prompt = ft_strjoin(prompt + 1, "$ ");
	free(cwd);
	return (prompt);
}

void	add_slash_to_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
}

int	init(char **env)
{
	signal(SIGINT, sigint_handler);
	var->env = env;
	var->path = ft_split(getenv("PATH"), ":");
	add_slash_to_path(var->path);
	var->pwd = getenv("PWD");
	var->oldpwd = getenv("OLDPWD");
	var->home = getenv("HOME");
	var->user = getenv("USER");
	return (0);
}

int	main(int ac, char **av, char **env)
{
	ssize_t	read;
	size_t	len;
	char	*line;

	setbuf(stdout, NULL);
	if (ac != 1)
		return (ft_putendl_fd("minishell: no arguments", STDERR_FILENO),
			FAILURE);
	var = ft_calloc(sizeof(t_var));
	init(env);
	len = 0;
	while (true)
	{
		line = readline(get_prompt());
		if (!line)
		{
			return (ft_exit(0), 0);
		}
		add_history(line);
		pass_the_input(line);
		free(line);
	}
}
