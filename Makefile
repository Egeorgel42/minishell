# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:09:43 by egeorgel          #+#    #+#              #
#    Updated: 2023/03/09 20:33:45 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FILES = srcs/main.c \
srcs/error.c \
srcs/builtins/mini_echo.c \
srcs/builtins/mini_env.c \
srcs/builtins/mini_export.c \
srcs/builtins/mini_pwd.c \
srcs/builtins/mini_unset.c \
srcs/builtins/mini_cd.c \
srcs/parsing/create_env.c \
srcs/parsing/sep_token.c \
srcs/piping/redirection.c \
srcs/piping/pipes.c \
srcs/utils/utils.c \

RDLINE = libs/readline
OBJ = ${FILES:.c=.o}
HDR = includes/minishell.h
NAME = minishell
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LFLAGS = -Llibs/libft -Llibs/readline/lib -lft -lreadline -I$(RDLINE)/include

all: $(NAME)

$(RDLINE):
	bash install_readline.sh

$(NAME): $(RDLINE) $(OBJ) $(HDR) Makefile
	cd libs/libft ; make bonus
	$(CC) $(LFLAGS) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	cd libs/libft ; make clean

fclean: clean
	rm -f $(NAME)
	rm -f libs/libft/libft.a
	rm -fR libs/readline

re: fclean all

.c.o: $(LIB) $(HDR) Makefile
	$(CC) $(CFLAGS) -I$(RDLINE)/include -c -o $@ $<

.PHONY: all clean fclean re
