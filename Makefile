# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:09:43 by egeorgel          #+#    #+#              #
#    Updated: 2023/03/08 18:14:46 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LFLAGS = -lreadline
FILES = main.c \
error.c \
builtins/mini_echo.c \
builtins/mini_env.c \
builtins/mini_export.c \
builtins/mini_pwd.c \
builtins/mini_unset.c \
builtins/mini_cd.c \
parsing/create_env.c \
parsing/sep_token.c \
parsing/prompt.c \
piping/redirection.c \
piping/pipes.c \
utils/utils.c \


OBJ = ${FILES:.c=.o}
HDR = minishell.h
NAME = minishell
LIB = libft/libft.a

all: $(NAME) $(LIB)

$(NAME): $(OBJ) $(HDR) Makefile
	cd libft ; make bonus
	$(CC) $(LFLAGS) $(CFLAGS) libft/libft.a $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	cd libft ; make clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.c.o: $(LIB) $(HDR) Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all clean fclean re
