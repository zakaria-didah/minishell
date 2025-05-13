#include "main.h"

t_builtins	*get_builtin(void)
{
	static t_builtins	builtin[] = {{"cd", ft_cd}, {"pwd", ft_pwd}, {"export",
			ft_export}, {"unset", ft_unset}, {"env", ft_env}, {"exit", ft_exit},
			{"echo", ft_echo}, {NULL, NULL}};

	return (builtin);
}

bool	exec_builtin(t_list *cmdlst)
{
	t_builtins	*builtin;
	char		*cmd;
	int			i;
	size_t		len;

	builtin = get_builtin();
	i = 0;
	if (!((t_cmd *)cmdlst->content)->args)
		return (false);
	cmd = ((t_cmd *)cmdlst->content)->args[0];
	len = ft_strlen(cmd);
	while (builtin[i].name)
	{
		if (!ft_strncmp(cmd, builtin[i].name, len)
			&& len == ft_strlen(builtin[i].name))
		{
			var->curr_cmd = cmd;
			if (red_builtin(cmdlst) < 0)
				return (var->exit_s = 1, true);
			return (var->exit_s = builtin[i].func(++((t_cmd *)cmdlst->content)->args),
				red_builtin(NULL), true);
		}
		i++;
	}
	return (false);
}
