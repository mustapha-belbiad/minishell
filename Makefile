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
	./src/norm1.c \
	./src/norm2.c \
	./src/norm3.c \
	./src/norm4.c \
	./builtins/ft_check_cmd.c \
	./builtins/env_link.c \
	./builtins/pwd_cd_fcnt.c \
	./builtins/export_fcnt.c \
	./builtins/export2_fcnt.c \
	./builtins/unset_fcnt.c \
	./builtins/echo_fcnt.c \
	./execute/ft_execute.c \
	./execute/redi_here.c \
	./execute/file_in.c \
	./signals/signals.c

FLAGS = -Wall -Wextra -Werror -I/Users/mbelbiad/goinfre/.brew/Cellar/readline/8.1.2/include 
ARG = -o

all : $(NAME)

# -g3  -fsanitize=address 

$(NAME): $(SRC)
	@make -C ./libft
	@$(CC) $(FLAGS) -lreadline $(SRC) $(ARG) minishel ./libft/libft.a -L/Users/mbelbiad/goinfre/.brew/Cellar/readline/8.1.2/lib


clean : 
	rm -f $(NAME)
	make clean -C ./libft
fclean : clean

re: fclean all