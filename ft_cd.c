#include "main.h"

char	*check_path(char **args)
{
	char	*path;

	path = NULL;
	if (ft_arrlen(args) > 1)
		return (ft_strerror("too many arguments\n"), NULL);
	if (args && args[0])
		path = args[0];
	else
		return (throw_error("cd: [relative or absolute path]"), NULL);
	return (path);
}

int	ft_cd(char **args)
{
	char	*path;

	__attribute__((cleanup(cleanup))) char *tmp;
	tmp = NULL;
	tmp = getcwd(NULL, 0);
	if (!tmp)
		(perror("getcwd"), var->oldpwd = var->pwd);
	else
	{
		var->oldpwd = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
	}
	path = check_path(args);
	if (!path)
		return (ERROR);
	if (chdir(path))
		return (perror("minishell: cd"), ERROR);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		(perror("cd: error retrieving current directory"));
	else
		var->pwd = ft_strdup(tmp);
	ft_setenv("OLDPWD", var->oldpwd);
	return (ft_setenv("PWD", var->pwd), SUCCESS);
}
