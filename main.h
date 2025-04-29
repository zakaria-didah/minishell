#ifndef MINISHELL_MAIN_H
# define MINISHELL_MAIN_H

# include "libft/libft.h"
# include "parser.h"
# include "signals.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// will explain later
void	cleanup(void *ptr);
# define auto_free __attribute__((cleanup(cleanup)))

// a boolean type
typedef enum s_bool
{
	FALSE,
	TRUE
} t_bool;

typedef enum s_status
{
	SUCCESS,
	ERROR,
	FAILURE
} t_status;

typedef enum s_builtin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NONE,
} t_builtin;


typedef struct s_wildcard
{
	int i;
	int j;

	int start_index;
	int match;
	int txt_len;
	int pat_len;
}	t_wildcard;

// a structure to store the bultin functions with hash table algorithm
typedef struct s_builtins
{
	char *name;
	int (*func)(char **args);
} t_builtins;

// if u want to add a global variable, please add it to the t_var structure.
// a structure to store the env variables and global variables
typedef struct t_var
{
	char **env;
	char *pwd;
	char *oldpwd;
	char *curr_cmd;
	t_builtin *bultin;

} t_var;

extern t_var *var;

// token types
typedef enum token_type
{
	CMD,
	WSPACE,
	PIPE,
	RED_IN,
	RED_OUT = 0,
	APPEND = 1,
	DQUOTE = 34,
	DOLLAR = 36,
	SQUOTE = 39,
	BQUOTE,
	WORD,
	HDOC

} token_type;

typedef struct s_token
{
	char *value;
	token_type type;
} t_token;

// a structure to store the command line
typedef struct s_cmd
{
	char **args;
	char *in;
	char *out;
	int append;
	char *hdoc;
} t_cmd;

//......utiles......
char **split_(const char *s );
bool	is_balanced(char *input);
size_t	ft_atos(char *num);
int	ft_exit(char **args);
char	*get_prompt(void);
int	ft_cd(char **args);
int	init(char **env);
int	ft_export(char **args);
int	ft_echo(char **args);
int	ft_env(char **args);
int	ft_unset(char **args);
void	throw_error(char *line);
int	exec(t_list *line);
int	pass_the_input(char *line);
char	*join_args(char **args);
char	*find_cmd(char *cmd);
void	add_slash_to_path(char **path);
int	ft_setenv(char *name, char *value);
void	red_out(char *file);
void	append(char *file);
char	*ft_getenv(char *name);
int	edit_env(char *name, char *value, t_bool APPEND);
void	red_in(char *file);
void	redirect(t_list *head);
void	ft_error(char *error);
void	ft_strerror(char *s);
char	*handel_dollar(int *i, char *input);
char **	expand(char *arg);
void	red_in(char *file);
void	red_out(char *file);
void	append(char *file);
// void	hdoc(char *file);
int	exec_cmd(t_list *cmd);
void	exec_child(char *path, char **args);
bool	exec_builtin(t_list *cmdlst);
void	execute(t_list *cmd_lst);
void heredoc(const char *delimiter);
int pipex(t_list *head);

//......parsing......
int check_next_pipe(t_list *head);

//.....testing......
void	parr(char **arr);
void	pl(t_list *head, int f);

#endif


/*
I know the filesystem is a bit messy, but I'm working on it.
I'll try to make it more organized when I'm done eating.
Don't miss with the momry management, it's a bit tricky, and it may blow up.
the final parsing phase is not stable and under construction,
	due to the lack of ideas. do we use AST or not? .
use this header file to give feedback, suggestions,
	or to ask for help. I don't use README files, that technology is outdated.
*/
