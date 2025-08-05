# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 11:29:21 by beldemir          #+#    #+#              #
#    Updated: 2025/08/05 17:15:06 by beldemir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINEFLAGS = -lreadline
SRCS =	src/main.c src/utils/wait_input.c src/utils/alpha_sort.c src/env.c \
	src/parser/parser.c src/parser/parser_utils.c src/parser/handle_redir_pipe.c \
	src/parser/parser_utils_libft.c src/execute/execute.c \
	src/execute/find_path.c src/execute/ft_split.c src/execute/utils.c \
	src/built_in/ft_echo.c src/built_in/ft_cd.c src/built_in/ft_pwd.c src/built_in/ft_exit.c \
	src/built_in/ft_env.c src/built_in/ft_export.c src/built_in/ft_unset.c \
	src/redir_pipe/utils.c src/redir_pipe/heredoc.c src/utils/safe_quit.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(GNLFILES) $(OBJS) -o $(NAME) $(READLINEFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re