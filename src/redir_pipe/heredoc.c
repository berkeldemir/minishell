/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:43:58 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/08 01:23:38 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief it will create a file called heredoc_tmp.txt and send it as a input.
/// @param data : data structure which is used everywhere.

static void	handle_sig_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	safe_quit(env_data(GET, NULL), NULL, 0);
	exit(130);
}

static void	heredoc_child(t_data *data, int fd, int i, char *line)
{
	int	j;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		j = -1;
		while (line[++j])
			if (line[j] != data->arglst[i].lmt[j])
				break ;
		if (line[j] == '\0' && data->arglst[i].lmt[j] == '\0')
			break ;
		(write(fd, line, ft_strlen(line)), write(fd, &"\n", 1));
		free(line);
	}
	free(line);
	close(fd);
	safe_quit(data, NULL, 0);
	exit(0);
}

static void	heredoc_parent(t_data *data, int pid)
{
	int		status;

	signal(SIGINT, handle_sigint_child);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		data->heredoc_fine = FALSE;
		exit_code(SET, 130);
	}
}

int	launch_heredoc(t_data *data, int i)
{
	int		fd;
	pid_t	pid;
	char	*line;

	env_data(SET, data);
	line = NULL;
	pid = fork();
	if (pid == 0)
	{
		fd = open(TMPFILE, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd < 0)
			return (perror("open heredoc"), safe_quit(data, NULL, 0), 1);
		(signal(SIGINT, handle_sig_heredoc), heredoc_child(data, fd, i, line));
	}
	else
		heredoc_parent(data, pid);
	return (0);
}
