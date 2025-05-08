#include "main.h"


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
		path = args[0];
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
