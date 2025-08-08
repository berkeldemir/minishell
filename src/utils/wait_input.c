/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:19:42 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/08 09:40:56 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*static char	*ms_ft_strdup(char *s)
{
	int		i;
	char	*toreturn;

	i = -1;
	toreturn = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!toreturn)
		return (NULL);
	while (s[++i] != '\0')
		toreturn[i] = s[i];
	toreturn[i] = '\0';
	return (toreturn);
}

static char	*get_display_path(char *path)
{
	char	*home;
	char	*result;

	home = getenv("HOME");
	if (home && strncmp(path, home, ft_strlen(home)) == 0) // /home/beldemir
	{
		if (path[ft_strlen(home)] == '\0')
			return (ms_ft_strdup("~"));
		result = ms_ft_strjoin(path + ft_strlen(home), "~");
		return (result);
	}
	return (ms_ft_strdup(path));
} */

static int	print_prompt(t_data *data)
{
	data->input = readline("\033[38;2;175;252;65mMINISHELL>₺ \033[0m");
	if (!data->input)
	{
		write(1, "exit\n", 5);
		free_env(data, TRUE);
		safe_free((void *)&data->name);
		return (1);
	}
	return (0);
}

void	handle_sigint_parent(int sig)
{
	(void)sig;
	exit_code(SET, 130);
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_child(int sig)
{
	(void)sig;
	exit_code(SET, 130);
	write(STDOUT_FILENO, "\n", 1);
}

void handle_sigquit(int sig)
{
    (void)sig;
	exit_code(SET, 131);
    write(2, "Quit (core dumped)\n", 19);
    signal(SIGQUIT, SIG_IGN);  // Varsayılan davranışı tekrar etkinleştir
    kill(getpid(), SIGQUIT);  // Gerçekten programı sonlandır
}

static int	assign_pipes(t_data *data)
{
	int	i;

	data->fds = malloc((2 * (data->cmd_count - 1)) * sizeof(int));
	if (!data->fds)
		return (1);
	i = -1;
	while (++i < data->cmd_count - 1)
		if (pipe(&data->fds[i * 2]) == -1)
			return (perror("pipe"), 1);
	i = -1;
	while (++i < data->cmd_count)
	{
		/*if (data->arglst[i].in)
			if (access(data->arglst[i].in, X_OK))
				return (perror("open infile"), 1);
		if (data->arglst[i].out)
			if (access(data->arglst[i].out, X_OK))
				return (perror("open outfile"), 1);*/
	}
	return (0);
}

void	wait_input(t_data *data)
{
	char	path[1023];
	
	while (1)
	{
		(signal(SIGQUIT, SIG_IGN), signal(SIGINT, handle_sigint_parent));
		if (getcwd(path, sizeof(path)) == NULL)
			return ;
		if (print_prompt(data) != 0)
			break ;
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			if (syntax_checker(data->input) != 0 || parser(data) != 0)
			{
				free_args(data);	
				continue ;
			}
			arglst_generator(data);
			if (!data->arglst || !data->arglst[0].args || \
			(!data->arglst[0].args[0] && (!data->arglst[0].lmt && \
			!data->arglst[0].in && !data->arglst[0].out)) || \
			assign_pipes(data) != 0)
			{
				(free_args(data), exit_code(SET, 1));
				continue ;
			}
			data->curr_env = env_converter(data);
			if (data->heredoc_fine == TRUE)
				exit_code(SET, executor(data));
			(free_args(data), free_env(data, FALSE));
			safe_free((void *)&data->fds);
		}
		free(data->input);
	}
}
