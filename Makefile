SRC= main.c parser.c signals.c utiles.c
OBJ= $(SRC:.c=.o)
CC= cc
CFLAGS=  -g
LDFLAGS= -lreadline 
lib= libft/libft.a
NAME= minishell


all: $(NAME)

$(NAME): $(lib) $(OBJ) 
	@echo "linking"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)  $(LDFLAGS) $(lib)

$(lib):
	@echo "Compiling libft"
	@make -C libft

clean:
	@echo "Cleaning"
	@rm -f $(OBJ)
	@$(MAKE) -C libft clean
	@echo "Cleaned"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
