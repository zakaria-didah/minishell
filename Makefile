SRC= main.c parser.c signals.c utiles.c exec.c echo.c \
	redirections.c ft_env.c error.c expand.c export.c ft_split_x.c \
	ft_heredoc.c
OBJ= $(SRC:.c=.o)
CC=gcc
CFLAGS=  -g3 #-fsanitize=address 
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
