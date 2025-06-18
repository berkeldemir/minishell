# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 11:29:21 by beldemir          #+#    #+#              #
#    Updated: 2025/06/18 15:35:16 by tmidik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = #-Wall -Wextra -Werror
READLINEFLAGS = -lreadline
SRCS =	src/main.c src/utils/wait_input.c src/env.c \
	src/parser/parser.c src/parser/parser_utils.c \
	src/parser/parser_utils_libft.c src/execute/execute.c \
	src/execute/find_path.c src/execute/ft_split.c src/execute/utils.c \
	src/built_in/echo.c src/built_in/cd.c
	
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