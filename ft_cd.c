#include "main.h"


int	ft_cd(char **args)
{
	char	*path;
	char	*home;
	int		stat;

	__attribute__((cleanup(cleanup))) char *tmp;
	stat = 0;
	tmp = NULL;
	tmp = getcwd(NULL, 0);
	if (!tmp)
		(perror("getcwd"), var->oldpwd = var->pwd, ERROR);
	else{
	var->oldpwd = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	}
	if (ft_arrlen(args) > 1)
		return (ft_strerror("too many arguments\n"), ERROR);
	if (args && args[0])
		path = args[0];
	else
		return (throw_error("cd: [relative or absolute path]"), ERROR);
	if (chdir(path))
		return (perror("minishell: cd"), ERROR);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		(perror("cd: error retrieving current directory"), ERROR);
	else
		var->pwd = ft_strdup(tmp);
	ft_setenv("OLDPWD", var->oldpwd);
	ft_setenv("PWD", var->pwd);
	return ( SUCCESS);
}
