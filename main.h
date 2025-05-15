/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:07:02 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/15 10:20:01 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft/garb.h"
# include "libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define HDOCFILE "/tmp/.heredoc_minishell"
# define SEP 0x1F
# define SEP2 0x1E
# define BUCKET_SIZE 255

typedef enum s_bool
{
	FALSE,
	TRUE
}							t_bool;

typedef enum s_status
{
	SUCCESS,
	ERROR,
	FAILURE
}							t_status;

typedef enum s_builtin
{
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NONE,
}							t_builtin;

typedef struct s_wildcard
{
	int						i;
	int						j;

	int						start_index;
	int						match;
	int						txt_len;
	int						pat_len;
}							t_wildcard;

typedef struct s_builtins
{
	char					*name;
	int						(*func)(char **args);
}							t_builtins;

typedef struct s_env
{
	char					*name;
	char					*value;
}							t_env;

typedef struct t_var
{
	t_list					*env;
	t_list					*bucket[BUCKET_SIZE + 1];
	char					*pwd;
	char					*oldpwd;
	char					*curr_cmd;
	volatile sig_atomic_t	hdoc;
	int						exit_s;
	volatile sig_atomic_t	child;

}							t_var;

extern t_var				*g_var;

typedef enum t_token_type
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
}							t_token_type;

typedef struct s_token
{
	char					*value;
	t_token_type			type;
}							t_token;

typedef struct s_red
{
	char					*file;
	t_token_type			type;

}							t_red;

// a structure to store the command line
typedef struct s_cmd
{
	char					**args;
	t_list					*in;
	t_list					*out;
}							t_cmd;

uint64_t					ft_atos(char *num);
char						**split_(const char *s);
bool						is_balanced(char *input);
int							ft_exit(char **args);
char						*get_prompt(void);
int							ft_cd(char **args);
int							init(char **env);
int							ft_export(char **args);
int							ft_echo(char **args);
int							ft_env(char **args);
int							ft_unset(char **args);
void						throw_error(char *line);
int							pass_the_input(char *line);
char						*join_args(char **args);
char						*find_cmd(char *cmd);
int							ft_setenv(char *name, char *value);
void						cleanup(void *ptr);
char						*ft_getenv(const char *name);
int							edit_env(char *name, char *value, t_bool APPEND);
int							redirect(t_list *head);
void						ft_error(char *error);
void						ft_strerror(char *s);
int							exec_cmd(t_list *cmd);
int							exec_child(char **args);
bool						exec_builtin(t_list *cmdlst);
void						execute(t_list *cmd_lst);
char						*heredoc(char *head);
int							pipex(t_list *head);
int							open_file(char *file, int append_redout_redin);
pid_t						fork_cmd(void);
int							check_next_pipe(t_list *head);
void						sort_alpha(char **arr);
t_red						*new_red(char *file, t_token_type type);
void						parr(char **arr);
void						pl(t_list *head, int f);
void						default_signal(void);
int							ft_pwd(char **args);
void						wait_for_it(pid_t pid, pid_t lastpid, int count);
void						ft_strerror(char *s);
void						ft_error(char *s);
int							check_is_in(char c, const char *s);

void						fill_bucket(char **env);
void						unset_env(char *name);
char						**envtoarr(void);

#endif
