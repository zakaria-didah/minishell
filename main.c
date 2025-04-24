#include "main.h"

t_var	*var = NULL;

int	ft_cd(char **args)
{
	char	*path;
	char	*home;
	int		stat;

	__attribute__((cleanup(cleanup))) char *tmp;
	stat = 0;
	tmp = NULL;
	if (ft_arrlen(args) > 1)
		return (ft_strerror("too many arguments\n"), ERROR);
	if (args && args[0])
	{
		path = args[0];
	}
	else
		return (throw_error("cd: [relative or absolute path]\n"), ERROR);
	if (chdir(path))
		return (perror("minishell: cd"), ERROR);
	var->oldpwd = var->pwd;
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (perror("cd: error retrieving current directory"), ERROR);
	var->pwd = ft_strdup(tmp);
	edit_env("PWD=", var->pwd, TRUE);
	return (edit_env("OLDPWD=", var->oldpwd, TRUE), SUCCESS);
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
	__attribute__((cleanup(cleanup))) char *line;
	if (ac != 1)
		return (ft_putendl_fd("minishell: no arguments", STDERR_FILENO),
			FAILURE);
	var = ft_calloc(sizeof(t_var), C_ARENA);
	init(env);
	while (true)
	{
		line = readline(get_prompt());
		if (!line)
		{
			return (ft_exit(0), 0);
		}
		add_history(line);
		pass_the_input(line);
	}
	return (0);
}
