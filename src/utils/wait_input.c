/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:19:42 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/07 12:24:24 by beldemir         ###   ########.fr       */
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

static void	print_prompt(t_data *data)
{
	data->input = readline("\033[38;2;175;252;65mMINISHELL>₺ \033[0m");
	//printf("%s\n", getcwd(NULL, 0));
	//printf("%s\n", data->input);
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
    write(1, "Quit (core dumped)\n", 19);
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
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint_parent);
		if (getcwd(path, sizeof(path)) == NULL)
			return ;
		print_prompt(data);
		//if (g_signal_received)
		//{
		//    g_signal_received = 0;  // Flag'i sıfırla
		//	continue;  // Prompt'u yeniden göster
		//}
		if (!data->input)
		{
			write(1, "exit\n", 5);
			free_env(data, TRUE);
			safe_free((void *)&data->program_name);
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			if (syntax_checker(data->input) != 0 || parser(data) != 0)
				continue ;
			//printf("-----after parser------\n");
			//arglst_generator(data); // data->args free yok.
			//printf("cmd_count: %i\n", data->cmd_count);
			/*int	i = -1;
			while (++i < data->cmd_count)
			{
				printf("%i\n", i);
				int	j = -1;
				while (data->arglst[i][++j].s != NULL)
					printf("[%i][%i]%s[%c]\n", i, j, data->arglst[i][j].s, data->arglst[i][j].token);
			}
			sleep(1000);*/
			arglst_generator(data);
			if (!data->arglst || !data->arglst[0].args || \
			(!data->arglst[0].args[0] && (!data->arglst[0].lmt && \
			!data->arglst[0].in && !data->arglst[0].out)) || \
			assign_pipes(data) != 0)
			{
				//write(2, "minishell: syntax error\n", 24);
				//exit_code(SET, 2);
				free_args(data);
				exit_code(SET, 1);
				continue ;
			}
			data->curr_env = env_converter(data);
			//printf("cmdcnt: %i\n", data->cmd_count);
			//if (assign_pipes(data) != 0)
			//	;
			signal(SIGINT, handle_sigint_child);
			exit_code(SET, executor(data));
			free_args(data);
			free_env(data, FALSE);
			safe_free((void *)&data->fds);
		}
		free(data->input);
	}
}
