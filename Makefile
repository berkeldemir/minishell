# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 11:29:21 by beldemir          #+#    #+#              #
#    Updated: 2025/06/14 22:08:52 by tmidik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = #-Wall -Wextra -Werror
READLINEFLAGS = -lreadline
SRCS =	src/main.c  src/utils/wait_input.c \
	src/parser/parser.c src/parser/parser_utils.c \
	 src/execute/find_path.c src/execute/utils.c \
	 src/execute/ft_split.c src/execute/execute.c \
	 src/built_in/echo.c src/built_in/pwd.c
	

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(READLINEFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re