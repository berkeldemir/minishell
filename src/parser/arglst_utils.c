/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:13:42 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/08 12:20:44 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_outfiles(t_data *data, int fd, int i, int k)
{
	if (data->arglst[k].out)
		free(data->arglst[k].out);
	data->arglst[k].out = ft_strdup(data->args[i + 1].s);
	if (data->args[i].token != APPEND)
		fd = open(data->arglst[k].out, O_CREAT | O_TRUNC, 0644);
	else
		fd = open(data->arglst[k].out, O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		data->arglst[k].run = FALSE;
		exit_code(SET, 1);
		return (perror("open outfile"), -1);
	}
	if (data->args[i].token == APPEND)
		data->arglst[k].append = TRUE;
	close(fd);
	return (0);
}

static int	open_infiles(t_data *data, int fd, int i, int k)
{
	if (data->arglst[k].in)
		free(data->arglst[k].in);
	data->arglst[k].in = ft_strdup(data->args[i + 1].s);
	fd = open(data->arglst[k].in, O_RDONLY);
	if (fd < 0)
	{
		data->arglst[k].run = FALSE;
		exit_code(SET, 1);
		return (perror("open infile"), -1);
	}
	close(fd);
	return (0);
}

int	handle_redirs_arglst(t_data *data, int i, int k)
{
	int	fd;

	fd = 0;
	if (data->args[i].token == APPEND || data->args[i].token == REDIR_OUT)
	{
		if (open_outfiles(data, fd, i, k) == -1)
			return (-1);
	}
	else if (data->args[i].token == REDIR_IN)
	{
		if (open_infiles(data, fd, i, k) == -1)
			return (-1);
	}
	else if (data->args[i].token == HEREDOC)
	{
		if (data->arglst[k].lmt)
			free(data->arglst[k].lmt);
		data->arglst[k].lmt = ft_strdup(data->args[i + 1].s);
		if (data->heredoc_fine == TRUE)
			launch_heredoc(data, k);
		if (data->arglst[k].in)
			free(data->arglst[k].in);
		data->arglst[k].in = ft_strdup(TMPFILE);
	}
	return (1);
}
