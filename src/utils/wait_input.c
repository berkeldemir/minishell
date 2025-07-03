/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:19:42 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/03 13:44:58 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ms_ft_strdup(char *s)
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
	if (home && strncmp(path, home, ms_ft_strlen(home)) == 0)
	{
		if (path[ms_ft_strlen(home)] == '\0')
			return (ms_ft_strdup("~"));
		result = ms_ft_strjoin(path + ms_ft_strlen(home), "~");
		return (result);
	}
	return (strdup(path));
}

static void	print_prompt(char *path)
{
	char	*display;

	display = get_display_path(path);
	printf("%s%s@:%s %s\n%s",
		GREEN, getenv("USER"), ORANGE, display, DEFAULT);
	free(display);
}

static void	handle_sigint(int sig)
{
	char	path[1023];

	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	if (getcwd(path, sizeof(path)) != NULL)
		print_prompt(path);
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
		print_prompt(path);
		data->input = readline("\033[38;2;8;99;117m>₺ \033[0m");
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
