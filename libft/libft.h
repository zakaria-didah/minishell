/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:06:33 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/15 10:59:21 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char				*ft_itoa(int n);
int					ft_isalpha(int c);
int					ft_isspace(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_arrlen(char **arr);
int					ft_lstsize(t_list *lst);
char				**ft_arrdup(char **arr);
size_t				ft_strlen(const char *s);
t_list				*ft_lstlast(t_list *lst);
size_t				ft_atoi(const char *str);
t_list				*ft_lstnew(void *content);
char				*ft_strdup(const char *s1);
void				ft_putnbr_fd(int n, int fd);
void				ft_bzero(void *s, size_t n);
int					is_in(char c, const char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_arrdel(char **arr, int elem);
char				**ft_arradd(char **s1, char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				**ft_arrjoin(char **s1, char **s2);
int					count_words(const char *s, char *c);
void				*ft_memset(void *b, int c, size_t len);
char				**ft_split(const char *s, char *charset);
char				*ft_strtok(char *str, const char *delim);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstremove(t_list **head, t_list *node);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstadd_front(t_list **lst, t_list *new);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(const char *s1, const char *set);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*create_word(const char *s, const char *c, int *j);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strinsert(char *s, char *txt, int index, int end);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_substr(const char *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

#endif
