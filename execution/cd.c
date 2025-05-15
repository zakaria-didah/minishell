#include "../main.h"

int	cd(char **argv)
{
	char	*pwd;
	char	*old_pwd;

	if (!argv)
		return (ft_putstr_fd("minishell: cd: only relative or absolute path\n", 2), FAILURE);
	if (argv[1])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), FAILURE);
	old_pwd = ft_getenv("PWD");
	if (chdir(argv[0]))
		return (perror("minishell: cd"), FAILURE);
	pwd = getcwd(NULL, 0);
	ft_setenv("OLDPWD", old_pwd);
	if (!pwd)
	{
		pwd = ft_strjoin(old_pwd, "/");
		pwd = ft_strjoin(pwd, argv[0]);
		ft_setenv("PWD", pwd);
		return (perror("minishell: cd: error retrieving current directory"), FAILURE);
	}
	return (ft_setenv("PWD", pwd), SUCCESS);
}