#ifndef MINISHELL_MAIN_H
# define MINISHELL_MAIN_H

# include "libft/libft.h"
# include "parser.h"
# include "signals.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_bultin
{
	char *name;
	int (*func)(char *line);
} t_bultin;

typedef struct t_var
{
	char **env;
	char **path;
	char *pwd;
	char *oldpwd;
	char *home;
	char *user;
	char *host;
	t_bultin *bultin;
	
} t_var;


extern t_var	*var;

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;

} t_env;

typedef struct s_redir
{
	char *file;
	int type;
	struct s_redir *next;

} t_redir;

typedef struct s_pipe
{
	char *cmd;
	struct s_pipe *next;

} t_pipe;

typedef enum flag{
	CMD,
	option,
	arg,
	pipe,
	red_in,
	red_out,
	expand
} flag;

typedef struct s_cmd
{
	int value;
	char *cmd;
	struct s_cmd *next;

} t_cmd;

//......utiles......
void	ft_exit(int status);
char *get_prompt(void);
void	ft_cd(char *line);
int	init(char **env);
void	ft_export(char *line);
int	ft_echo(char *line);
void	ft_env(void);
void	ft_unset(char *line);
void	ft_exec(char *line);

//......parsing......


#endif