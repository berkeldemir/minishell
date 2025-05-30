/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:21 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/30 19:58:45 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define GREEN "\033[38;2;175;252;65m"
# define BLUE "\033[38;2;8;99;117m"
# define ORANGE "\033[38;2;255;202;58m"
# define DEFAULT "\033[0m"

# define COMMAND 'c'
# define ARGUMENT 'a'
# define DQUOTE 'd'
# define SQUOTE 's'
# define PIPE '|'
# define REDIR_IN '<'
# define REDIR_OUT '>'
# define APPEND 'A'
# define HEREDOC 'H'

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef struct s_args
{
	char	*s;
	char	token;
	int		index;
}	t_args;

typedef struct s_tmps
{
	int	len;
	int	arg_i;
	int	quote;
}	t_tmps;

typedef struct s_data
{
	char	*program_name;
	char	**env;
	char	*input;
	t_args	*args;
	t_tmps	tmps;
	int		arg_count;
}	t_data;

//-------- PARSER ------------
int		put_value_in_place(t_data *data, char *str, int j);
char	*get_env_val(t_data *data, char *key);
int		count_args(char *str, t_data *data);
int		parser(t_data *data);

//-------- LIBFT --------------
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *s);


//-------- UTILS ---------------
int		is_space(char c);
int		exit_freely(t_data *data);

#endif
