#include "main.h"



t_bultin	**get_bin(void)
{
	static t_bultin	builtin[] = {
		{"cd", ft_cd},
		{"echo", ft_echo},
		{"export", ft_export},
		{"unset", ft_unset},
		{"env", ft_env},
		{"exit", ft_exit},
		{NULL, NULL}
	};
	return (&builtin);
}

t_var	*var = NULL;

void ft_export(char *line)
{
	char **args;
	char *value;
	char *name;
	int i;

	i = 0;
	int  j = 0;
	args = ft_split(line + 6, ' ');
	while(args[i]){
		while (args[i][j] && args[i][j] != '=')
		{
			j++;
		}
		value = ft_strtrim(args[i] + j+1, "\"\'");
		name = args[i];
		name[j] = '\0';
		setenv(name, value, 1);
		j = 0;
		i++;
	}
	ft_remove(args);
}

int ft_echo(char *line)
{
	char *str;
	int i;
	int j;
	char *var;

	i = 0;
	//str = ft_strtrim(line + 4, " \"\'");
	if ()
	
	while (str[i] != '\0')
	{
		ft_putstr_fd(line, STDOUT_FILENO);
		if (flag){
			write(STDOUT_FILENO, &str[i], 1);
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	ft_remove(str);
	return (0);
}

void ft_cd(char *line)
{
	char *path;
	char *home;

	path = ft_strtrim(line + 2, " ");
	if (ft_strncmp(path, "~", 1) == 0)
	{
		home = ft_strdup(getenv("HOME"));
		path = ft_strjoin(home, path + 1);
		ft_remove(home);
	}
	if (path[0] == '\0')
	{
		home = ft_strdup(getenv("HOME"));
		chdir(home);
		ft_remove(home);
	}
	else
	{
		chdir(path);
	}
	ft_remove(path);
}

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

int	init()
{
	signal(SIGINT, sigint_handler);
	var->env = getenv("ENV");
	var->path = ft_split(getenv("PATH"), ':');
	var->pwd = getenv("PWD");
	var->oldpwd = getenv("OLDPWD");
	var->home = getenv("HOME");
	var->user = getenv("USER");
	t_bultin bultin[] = {
		{"cd", ft_cd},
		{"echo", ft_echo},
		{"export", ft_export},
		{"unset", ft_unset},
		{"env", ft_env},
		{"exit", ft_exit},
		{NULL, NULL}
	};
	return (0);
}

int	main()
{
	ssize_t	read;
	size_t	len;
	char	*line;

	var = ft_calloc(1, sizeof(t_var));
	init();
	len = 0;
	while (true)
	{
		line = readline(get_prompt());
		if (!line)
		{
			return (ft_exit(0), 0);
		}
		add_history(line);
		parse(line);
		free(line);
	}
}
