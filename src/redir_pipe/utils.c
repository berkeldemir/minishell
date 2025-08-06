/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:38:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/06 20:00:17 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_redirs_arglst(t_data *data, int i, int k)
{
	int	fd;

	if (data->args[i].token == APPEND || data->args[i].token == REDIR_OUT)
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
			data->exit_code = 1;
			return (perror("open outfile"), -1);
		}
		close(fd);
	}
	else if (data->args[i].token == REDIR_IN)
	{
		if (data->arglst[k].in)
			free(data->arglst[k].in);
		data->arglst[k].in = ft_strdup(data->args[i + 1].s);
		fd = open(data->arglst[k].in, O_RDONLY);
		if (fd < 0)
		{
			data->arglst[k].run = FALSE;
			data->exit_code = 1;
			return (perror("open infile"), -1);
		}
	}
	else if (data->args[i].token == HEREDOC)
	{
		if (data->arglst[k].lmt)
			free(data->arglst[k].lmt);
		data->arglst[k].lmt = ft_strdup(data->args[i + 1].s);
		launch_heredoc(data, k);
		if (data->arglst[k].in)
			free(data->arglst[k].in);
		data->arglst[k].in = ft_strdup(TMPFILE);
	}
	if (data->args[i].token == APPEND)
		data->arglst[k].append = TRUE;
	return (1);
}

static int	find_size_arglst(t_data *data, int *start, int total, int k)
{
	int	i;
	int	ret;
	int	count;

	count = 0;
	i = *start - 1;
	ret = 0;
	while (++i < total && data->args[i].token != PIPE)
	{
		if (data->args[i].token == WORD)
			count++;
		else if (ret != -1)
		{
			ret = handle_redirs_arglst(data, i, k);
			i += 1;
		}
		else
			i += 1;
	}
	return (count);
}

static int	assignment_arglst(t_data *data)
{
	int	limit;
	int	i;
	int	j;
	int	k;

	i = -1;
	k = -1;
	while (++k >= 0 && ++i < data->arg_count && k < data->cmd_count)
	{
		limit = find_size_arglst(data, &i, data->arg_count, k);
		if (limit < 0)
			return (-1);
		//if (limit < 0)
		//	return (-1);
		/*if (data->arglst[k].in)
			printf("k:%i\tin:%s\n", k, data->arglst[k].in);
		if (data->arglst[k].out)
			printf("k:%i\tout:%s\n", k, data->arglst[k].out);
		if (data->arglst[k].lmt)
			printf("k:%i\tlmt:%s\n", k, data->arglst[k].lmt);
		if (data->arglst[k].append == TRUE)
			printf("k:%i\tappend:%i\n", k, data->arglst[k].append);*/
		data->arglst[k].args = (char **)malloc(sizeof(char *) * (limit + 1));
		if (!data->arglst[k].args)
			return (0);
		if (limit == 0)
			data->arglst[k].args[0] = NULL;
		j = -1;
		while (++j < limit)
		{
			if (i < data->arg_count && data->args[i].token == PIPE)
				i++;
			while (i < data->arg_count && data->args[i].token != WORD)
				i += 2;
			if (i < data->arg_count)
				data->arglst[k].args[j] = ft_strdup(data->args[i].s);
			else
				data->arglst[k].args[j] = NULL;
			//printf("k:%i\targs[%i]:%s\n", k, j, data->arglst[k].args[j]);
			i++;
		}
		while (i < data->arg_count && data->args[i].token != PIPE)
			i += 2;
		data->arglst[k].args[j] = NULL;
	}
	return (0);
}

int	arglst_generator(t_data *data)
{
	int	i;

	i = 0;
	data->cmd_count = 1;
	while (++i < data->arg_count)
		if (data->args[i].token == PIPE)
			data->cmd_count++;
	data->arglst = (t_arglst *)malloc(sizeof(t_arglst) * (data->cmd_count + 1));
	if (!data)
		return (-1);
	i = -1;
	while (++i <= data->cmd_count)
	{
		data->arglst[i].args = NULL;
		data->arglst[i].in = NULL;
		data->arglst[i].out = NULL;
		data->arglst[i].lmt = NULL;
		data->arglst[i].run = TRUE;
		data->arglst[i].append = FALSE;
	}
	if (assignment_arglst(data) < 0)
		return (-1);
	return (0);
}
