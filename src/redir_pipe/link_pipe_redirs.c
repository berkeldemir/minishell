/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_pipe_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:47:00 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/08 11:14:40 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	link_pipe_ends_and_redirs(t_data *data, int i)
{
	int	fd;

	if (data->arglst[i].in)
	{
		fd = open(data->arglst[i].in, O_RDONLY);
		if (fd < 0)
			return (perror("open infile"), 1);
		(dup2(fd, STDIN_FILENO), close(fd));
	}
	else if (i > 0)
		dup2(data->fds[(i - 1) * 2], STDIN_FILENO);
	if (data->arglst[i].out)
	{
		fd = open(data->arglst[i].out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (perror("open outfile"), 1);
		(dup2(fd, STDOUT_FILENO), close(fd));
	}
	else if (i < data->cmd_count - 1)
		dup2(data->fds[(i * 2) + 1], STDOUT_FILENO);
	i = 0;
	while (i < 2 * (data->cmd_count - 1))
		close(data->fds[i++]);
	return (0);
}
