/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:21 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/12 18:39:55 by tmidik           ###   ########.fr       */
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

typedef struct s_data
{
	char	*input;
	char	**args;
	char	**envp;
	int		arg_count;
}				t_data;

//-------- MAIN FUNCS ---------
void	wait_input(t_data *data);
int		parser(t_data *data);
int		free_array(char	**str);

//-------- PARSER UTILS --------
char	*ft_strndup(char *str, size_t n);
int		is_space(char c);
int		word_len(char *str);
int		count_words(char *str);

//-------- EXECUTE_UTILS -------
int	ft_strncmp(char *s1, char *s2, int n);
int	ft_strcmp(char *s1, char *s2);

#endif
