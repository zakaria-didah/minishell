#include "main.h"

t_var	*var = NULL;

int	ft_export(char **args)
{
	char	*value;
	char	*name;
	int		i;
	int		j;

	value = NULL;
	name = NULL;
	i = 0;
	j = 0;
	while (args[i])
	{
		while (args[i][j] && args[i][j] != '=')
			j++;
		name = ft_substr(args[i], 0, j);
		if (args[i][j] == '=')
		{
			j++;
			value = args[i] + j;
		}
		ft_setenv(name, value);
		j = 0;
		i++;
	}
	return SUCCESS;
}

int	ft_cd(char **args)
{
	char	*path;
	char	*home;
	int		stat;
	char	*tmp;

	stat = 0;
	if (ft_arrlen(args) > 1)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), ERROR);
	if (args && args[0])
	{
		path = args[0];
	}
	else
		return (throw_error("cd: [relative or absolute path]"), ERROR);
	if (chdir(path))
		return (perror("minishell: cd"), ERROR);
	var->oldpwd = var->pwd;
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (perror("cd"), ERROR);
	var->pwd = ft_strdup(tmp);
	free(tmp);
	edit_env("PWD=", var->pwd, true); 
	return edit_env("OLDPWD=", var->oldpwd, true), SUCCESS;
}

/*to get a prompt with the current working dir.*/
char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;
	int		option;

	option = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		option = TRUE;
		cwd = ft_getenv("PWD");
	}
	prompt = ft_strrchr(cwd, '/') + 1;
	prompt = ft_strjoin(prompt, "$> ");
	if (!option)
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
	return 0;
}
