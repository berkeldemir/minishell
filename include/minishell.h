/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:21 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/06 20:21:23 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>

# define GREEN "\033[38;2;175;252;65m"
# define BLUE "\033[38;2;8;99;117m"
# define ORANGE "\033[38;2;255;202;58m"
# define DEFAULT "\033[0m"

# define WORD 'w'
# define PIPE '|'
# define REDIR_IN '<'
# define REDIR_OUT '>'
# define APPEND 'A'
# define HEREDOC 'H'
# define TMPFILE "kdzuzbreusvcuvdzi"

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

typedef struct s_arglst
{
	char	**args;
	char	*in;
	char	*out;
	char	*lmt;
	t_bool	append;
	t_bool	run;
}	t_arglst;

typedef struct s_tmps
{
	int	len;
	int	arg_i;
	int	quote;
}	t_tmps;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char		*program_name;
	int			*fds;
	int			stdin_dup;
	int			stdout_dup;
	char		*input;
	int			arg_count;
	char		cwd[4096];
	int			cmd_count;
	int			exit_code;
	char		**curr_env;
	t_args		*args;
	t_arglst	*arglst;
	t_env		*env;
	t_tmps		tmps;
}	t_data;

//-------- PARSER ------------
int		parser(t_data *data);
int		parser_syntax_checker(t_data *data);
int		count_args(char *str, t_data *data);
int		count_handle_redir_pipe(char *input, int *count);
int		calc_handle_redir_pipe(char *input, int *len, int *i);
int		assign_handle_redir_pipe(t_data *data, char *input, int *i, int *j);
char	*get_env_val(t_data *data, char *key);
int		put_value_in_place(t_data *data, char *str, int *j);
int		is_redir_pipe(char c);
int		is_srp(char c);

//-------- UTILS --------------
int		is_space(char c);
int		is_quote(char c);
int		is_alnum(char c);
int		is_alpha(int i);
int		is_valid_identifier(char *str);

int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *s2, char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
int		ft_atoi(const char *str, long *tab_num);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_itoa(int n);

//-------- EXECUTE -------------
int		syntax_checker(char *input);
int		execute(t_data *data, int i, char **current_env);
int		executor(t_data *data);
char	*get_command_path(char *str, t_data *data);
void	handle_sigint_child(int sig);
void	handle_sigint_parent(int sig);
void	handle_sigquit(int sig);
void	wait_input(t_data *data);

//-------- BUILT-IN -------------
int		ft_echo(t_data *data, char **args);
int		ft_cd(t_data *data, char **args);
int		ft_pwd(t_data *data);
int		ft_exit(t_data *data, char **args);
int		ft_env(t_data *data);
int		ft_export(t_data *data, char **args);
int		ft_unset(t_data *data, char **args);

//-------- UTILS ---------------
int		exit_freely(t_data *data);
char	**ft_split(char *s, char c);
void	free_array(char **array);
void	alpha_sort(t_env **array, int size);

//--------  ENV  -------------- 
t_env	*env_new(char *key, char *value);
void	env_add_back(t_env **lst, t_env *new);
char	**env_converter(t_data *data);

//------- REDIR & PIPE ------------
int		arglst_generator(t_data *data);
int		launch_heredoc(t_data *data, int i);

void	safe_free(void **ptr);
int		link_pipe_ends_and_redirs(t_data *data, int i);
void	*ft_calloc(int size);
void	safe_quit(t_data *data, char **extra, int max);
void	free_env(t_data *data, t_bool free_all);
void	free_args(t_data *data);

#endif
