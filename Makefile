NAME = minishel
CC = cc
SRC = main_parc.c \
	./src/lexer.c \
	./src/token.c \
	./src/lexer1.c \
	./src/linked_outils.c \
	./src/outils.c \
	./src/parser.c \
	./src/parser1.c \
	./src/get_env.c \
	./src/expand_dollar.c \
	./src/lexer_dollar.c \
	./src/end_vers_outils.c \
	./src/end_vers.c \
	./src/get_list_of_cmd.c \
	./builtins/ft_check_cmd.c \
	./builtins/env_link.c \
	./execute/ft_execute.c \
	./execute/redi_here.c \
	./execute/file_in.c \
	./signals/signals.c
	
RDLINE  := -L /Users/mbelbiad/goinfre/.brew/opt/readline/lib -I /Users/mbelbiad/goinfre/.brew/opt/readline/include

FLAGS = -Wall -Wextra -Werror
ARG = -o

all : $(NAME)

# -g3  -fsanitize=address 

$(NAME): $(SRC)
	@make -C ./libft
	@$(CC) $(FLA) -lreadline $(SRC) $(RDLINE) $(ARG) minishel ./libft/libft.a 

clean : 
	rm -f $(NAME)
	make clean -C ./libft
fclean : clean

re: fclean all