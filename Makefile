# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:09:43 by egeorgel          #+#    #+#              #
#    Updated: 2023/04/28 20:07:53 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FILES = main.c \
error.c \
history.c \
builtins/cd_utils.c \
builtins/cd_utils2.c \
builtins/export_utils.c \
builtins/mini_echo.c \
builtins/mini_env.c \
builtins/mini_export.c \
builtins/mini_pwd.c \
builtins/mini_unset.c \
builtins/mini_cd.c \
builtins/mini_exit.c \
parsing/create_env.c \
parsing/sep_token.c \
parsing/sep_token_utils.c \
parsing/get_env.c \
parsing/get_env_utils.c \
piping/redirection.c \
piping/heredoc.c \
piping/child_process.c \
piping/execution_call.c \
piping/pipes.c \
utils/env_utils.c \
utils/start_env.c \
utils/list-pid_utils.c \
utils/utils1.c \
utils/utils2.c \
utils/utils3.c \
signals/signals.c \
signals/term_attr.c \
signals/sig_print.c \

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
LFLAGS = -Llibs/readline/lib -Llibs/libft -lft -lreadline -lhistory -I$(RDLINE)/include #-ltinfo
#if you are on Linux, uncomment the -ltinfo for the project to compile, or comment it if you are on MacOs.
SRCS = $(addprefix srcs/, $(FILES))
OBJ = ${SRCS:.c=.o}
RDLINE = libs/readline
LIBFT = libs/libft/libft.a
HDR = includes/minishell.h
NAME = minishell
all: $(NAME)

$(RDLINE):
	bash install_readline.sh

$(LIBFT):
	cd libs/libft ; make bonus

$(NAME): $(RDLINE) $(LIBFT) $(OBJ) $(HDR) Makefile
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	cd libs/libft ; make clean

fclean: clean
	rm -f $(NAME)
	rm -f libs/libft/libft.a
	rm -fR libs/readline

re: fclean all

.c.o: $(HDR) Makefile
	$(CC) $(CFLAGS) -I$(RDLINE)/include -c -o $@ $<

.PHONY: all clean fclean re
