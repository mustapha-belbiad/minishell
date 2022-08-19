# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-kouc <ael-kouc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 01:36:33 by ael-kouc          #+#    #+#              #
#    Updated: 2022/06/19 19:50:03 by ael-kouc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
SRC = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strlcpy.c ft_strlen.c ft_tolower.c ft_toupper.c ft_strlcat.c ft_atoi.c \
		ft_bzero.c ft_memset.c ft_strchr.c ft_strncmp.c ft_strrchr.c ft_memcpy.c ft_putchar_fd.c ft_memmove.c ft_strdup.c ft_memchr.c ft_memcmp.c \
		ft_strnstr.c ft_calloc.c ft_substr.c ft_putstr_fd.c ft_strjoin.c ft_putnbr_fd.c ft_putendl_fd.c ft_itoa.c ft_strtrim.c ft_strmapi.c \
		ft_striteri.c ft_split.c ft_realloc.c ft_strcat.c ft_putstr.c
OBJS = ${SRC:.c=.o}
FLAGS = -Wall -Wextra -Werror
ARG = -c

all : $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	
$(OBJS):
	$(CC) $(FLAGS) $(SRC) $(ARG)

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re: fclean all