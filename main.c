#include "main.h"

t_var	*var = NULL;

/*to get a prompt with the current working dir.*/
char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;
	int		option;

	option = 0;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		prompt = ft_strdup(cwd);
		free(cwd);
		cwd = ft_strrchr(prompt, '/') + 1;
	}
	else
	{
		option = TRUE;
		cwd = ft_getenv("PWD");
		if (!cwd)
		{
			cwd = ft_strdup("seriously");
		}
	}
	if (ft_strchr(cwd, '/'))
		cwd = ft_strrchr(cwd, '/') + 1;
	prompt = ft_strjoin(cwd, "$> ");
	return (prompt);
}


int	pass_the_input(char *line)
{
	t_list	*head;
	t_list	*cmd_lst;

	line = ft_strtrim(line, " ");
	if (!*line)
		return (var->exit_s = SUCCESS);
	if (!is_balanced(line))
		return (throw_error(NULL), var->exit_s = FAILURE);
	head = tokenize(line);
	cmd_lst = parse(head);
	if (!cmd_lst)
		return (var->exit_s = FAILURE);
	execute(cmd_lst);
	return (0);
}

int	init(char **env)
{
	ft_bzero(var, sizeof(t_var));
	var->env = env;
	__attribute__((cleanup(cleanup))) char *tmp = getcwd(NULL, 0);
	if (tmp){
		ft_setenv("PWD", tmp);
		var->pwd = ft_strdup(tmp);
	}
	else
	{
		perror("minishell: error retrieving current directory");
		var->pwd = ft_getenv("PWD");
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	(void)av;

	if (ac != 1)
		return (ft_putendl_fd("minishell: no arguments", 2), FAILURE);
	var = ft_calloc(sizeof(t_var), C_TRACK);
	init(env);
	line = NULL;
	while (true)
	{
		default_signal();
		line = readline(get_prompt());
		if (!line)
		{
			return (ft_exit(0), 0);
		}
		add_history(line);
		pass_the_input(line);
		reset_arena();
		free(line);
	}
	return (0);
}
