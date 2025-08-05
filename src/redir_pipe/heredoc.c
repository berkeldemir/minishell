/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:43:58 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/05 17:16:16 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief it will create a file called heredoc_tmp.txt and send it as a input.
/// @param data : data structure which is used everywhere.

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	//write(STDOUT_FILENO, "\n", 1);
	exit(0);
}

int	launch_heredoc(t_data *data, int i)
{
	int		j;
	int		fd;
	pid_t	pid;
	char	*line;

	//if (access(TMPFILE, F_OK) == 0)
	//	return (printf("minishell: %s already exist, remove it.", TMPFILE), 1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		fd = open(TMPFILE, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd < 0)
			return (perror("open heredoc"), safe_quit(data, NULL, 0), 1);
		line = readline("> ");
		while (line)
		{
			j = -1;
			while (line[++j])
				if (line[j] != data->arglst[i].lmt[j])
					break ;
			if (line[j] == '\0' && data->arglst[i].lmt[j] == '\0')
				return (free(line), close(fd), 0);
			write(fd, line, ft_strlen(line));
			write(fd, &"\n", 1);
			free(line);
			line = readline("> ");
		}
	}
	else
	{
		signal(SIGINT, handle_sigint_child);
		waitpid(pid, NULL, 0);
	}
			
	return (0);
}
