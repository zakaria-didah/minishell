/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:56 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/17 00:24:30 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "main.h"

t_list	*parse(t_list *tokens);
int		parse_(t_list **tokens, t_cmd *cmd);
int		parse_append(t_list **tokens, t_cmd *cmd);
int		parse_redout(t_list **tokens, t_cmd *cmd);
int		parse_redin(t_list **tokens, t_cmd *cmd);
int		parse_heredoc(t_list **tokens, t_cmd *cmd);
t_red	*new_red(char *file, t_token_type type);
void	handel_redin(char *input, int *i, t_token *token);
void	handel_redout(char *input, int *i, t_token *token);
void	handel_word(char *input, int *i, t_token *token);
int		red_builtin(t_list *head);
t_list	*tokenize(char *input);
void	skip_quote(char *arg, int *i);
char	*get_ifs(void);
char	**quet_remove(char **arg);
char	**check_wildcard(char **res);
void	sep(unsigned int i, char *s);
char	*handel_dollar(int *i, char *input);
char	**expand(char *arg);
void	add_slash_to_path(char **path);
char	**expand(char *arg);
char	*expand_vars(char *arg, bool here_doc);

#endif