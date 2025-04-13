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
}

void	ft_error(char *s)
{
	size_t	len;
	char	prefix[ft_strlen(var->curr_cmd) + 3];

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
	char	*tmp;

	stat = 0;
	if (ft_arrlen(args) > 1)
		return (ft_error(NULL), ERROR);
	if (args && args[0])
	{
		path = args[0];
	}
	else
		return (throw_error("cd: [relative or absolute path]"), ERROR);
	stat = chdir(path);
	if (stat != SUCCESS)
		return (ft_error(ft_strjoin(args[0], ": ")), ERROR);
	var->oldpwd = var->pwd;
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (ft_putendl_fd(strerror(errno),2), ERROR);
	var->pwd = ft_strdup(tmp);
	free(tmp);
	edit_env("PWD=", var->pwd, true);
	edit_env("OLDPWD=", var->oldpwd, true);
}
/*to get a prompt with the current working dir.*/
char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;
	int		option;

	option = 0;
	cwd = getcwd(NULL, 0);
	// printf("%s\n", cwd);
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
}
