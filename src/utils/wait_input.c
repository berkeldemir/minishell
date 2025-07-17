/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:19:42 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/17 18:16:20 by beldemir         ###   ########.fr       */
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
	printf("%s\n", getcwd(NULL, 0));
	printf("%s\n", data->input);
}

void handle_sigint(int sig)
{
    (void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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
			parser(data);
			execute(data);
		}
		free(data->input);
	}
}
