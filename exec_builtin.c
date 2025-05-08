#include "main.h"


bool	exec_builtin(t_list *cmdlst)
{
	t_builtins	builtin[] = {{"cd", ft_cd}, {"echo", ft_echo}, {"export",
			ft_export}, {"unset", ft_unset}, {"env", ft_env}, {"exit", ft_exit},
			{"pwd", ft_pwd}, {NULL}};
	char		*cmd;
	int			i;
	size_t		len;

	i = 0;
	cmd = ((t_cmd *)cmdlst->content)->args[0];
	len = ft_strlen(cmd);
	while (builtin[i].name)
	{
		if (!ft_strncmp(cmd, builtin[i].name, len)
			&& len == ft_strlen(builtin[i].name))
		{
			var->curr_cmd = cmd;
            if (red_builtin(cmdlst)<0)
                return (var->exit_s = 1, true);
			return (var->exit_s = builtin[i].func(++((t_cmd *)cmdlst->content)->args),
				red_builtin(NULL), true);
		}
		i++;
	}
	return (false);
}