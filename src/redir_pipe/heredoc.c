/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:43:58 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/31 13:14:19 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief it will create a file called heredoc_tmp.txt and send it as a input.
/// @param data : data structure which is used everywhere.

int	launch_heredoc(t_data *data, int i)
{
	int		j;
	int		fd;
	char	*line;

	if (access(TMPFILE, F_OK) == 0)
		return (printf("minishell: %s already exist, remove it.", TMPFILE), 1);
	fd = open(TMPFILE, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (perror("fd"), 1);
	write(1, "> ", 2);
	line = get_next_line(0);
	while (line)
	{
		j = -1;
		while (line[++j])
			if (line[j] != data->arglst[i].lmt[j])
				break ;
		if (line[j] == '\n')
			return (free(line), close(fd), 0);
		write(fd, line, ft_strlen(line));
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	return (0);
}
