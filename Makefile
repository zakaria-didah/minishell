SRC= main.c parser.c signals.c utiles.c exec.c echo.c ft_unset.c pipe.c\
	redirections.c ft_env.c error.c  export.c	ft_exit.c find_cmd.c\
	ft_heredoc.c expand/expand_utils.c expand/expand.c ft_cd.c exec_builtin.c \
	wildcard.c	tokenize.c
OBJ= $(SRC:.c=.o)
CC=cc
CFLAGS=  -g3 #-fsanitize=address #-Wall -Wextra -Werror  
LDFLAGS= -lreadline 
lib= libft/libft.a
NAME= minishell


all: $(NAME)


$(NAME): $(lib) $(OBJ) 
	@echo -n "linking "
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)  $(LDFLAGS) $(lib)

%.o: %.c
	@echo "Compiling $< "
	@$(CC) $(CFLAGS) -c $< -o $@

$(lib):
	@echo "Compiling libft"
	@make -C libft bonus >/dev/null

clean:
	@$(MAKE) -C libft clean >/dev/null
	@rm -f $(OBJ)
	@echo "Cleaned"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean >/dev/null

re: fclean all
	@make clean > /dev/null

.PHONY: all clean fclean re
