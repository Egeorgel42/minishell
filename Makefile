# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:09:43 by egeorgel          #+#    #+#              #
#    Updated: 2023/03/03 18:33:42 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LFLAGS = -lreadline
FILES = main.c prompt.c error.c redirection.c utils.c fd_utils.c sep_token.c
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
