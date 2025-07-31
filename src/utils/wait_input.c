/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:19:42 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/31 13:07:08 by beldemir         ###   ########.fr       */
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
	if (home && strncmp(path, home, ms_ft_strlen(home)) == 0) // /home/beldemir
	{
		if (path[ms_ft_strlen(home)] == '\0')
			return (ms_ft_strdup("~"));
		result = ms_ft_strjoin(path + ms_ft_strlen(home), "~");
		return (result);
	}
	return (ms_ft_strdup(path));
} */

static void	print_prompt(t_data *data)
{
	data->input = readline("\033[38;2;8;99;117mMINISHELL>₺ \033[0m");
	//printf("%s\n", getcwd(NULL, 0));
	//printf("%s\n", data->input);
}

void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	assign_pipes(t_data *data)
{
	int	i;

	data->fds = malloc((2 * (data->cmd_count - 1)) * sizeof(int));
	if (!data->fds)
		return ;
	i = -1;
	while (++i < data->cmd_count -1)
		if (pipe(&data->fds[i * 2]) == -1)
			(perror("pipe"), exit(EXIT_FAILURE));
}

void	wait_input(t_data *data)
{
	char	path[1023];
	
	signal(SIGINT, handle_sigint);
	while (1)
	{
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
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			if (syntax_checker(data->input) != 0 || parser(data) != 0)
				continue ;
			//printf("-----after parser------\n");
			arglst_generator(data); // data->args free yok.
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
			if (!data->arglst || !data->arglst[0].args || !data->arglst[0].args[0])
			{
				write(2, "minishell: empty command\n", 26);
				continue;
			}
			if (data->curr_env)
				free(data->curr_env);
			data->curr_env = env_converter(data);
			//printf("cmdcnt: %i\n", data->cmd_count);
			assign_pipes(data);
			executor(data);
			//free(curr_env);
		}
		free(data->input);
	}
}
