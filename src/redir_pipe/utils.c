/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:38:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/31 13:11:55 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_redirs_arglst(t_data *data, int i, int k)
{
	char	*str;
	int		fd;

	if (data->args[i].token == APPEND || data->args[i].token == REDIR_OUT)
	{
		str = ft_strdup(data->args[i + 1].s);
		if (data->args[i].token == REDIR_OUT)
		{
			fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				(perror("open outfile"), exit(1));
			close(fd);
		}
		data->arglst[k].out = str;
	}
	else if (data->args[i].token == REDIR_IN)
		data->arglst[k].in = ft_strdup(data->args[i + 1].s);
	else if (data->args[i].token == HEREDOC)
		data->arglst[k].lmt = ft_strdup(data->args[i + 1].s);
	if (data->args[i].token == APPEND)
		data->arglst[k].append = TRUE;
	else
		data->arglst[k].append = FALSE;
	return (1);
}

static int	find_size_arglst(t_data *data, int *start, int total, int k)
{
	int	i;
	int	count;

	count = 0;
	i = *start - 1;
	while (++i < total && data->args[i].token != PIPE)
	{
		if (data->args[i].token == WORD)
			count++;
		else
			i += handle_redirs_arglst(data, i, k);
	}
	return (count);
}

static void	assignment_arglst(t_data *data)
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
		data->arglst[k].args = (char **)malloc(sizeof(char *) * (limit + 1));
		j = -1;
		while (++j < limit)
		{
			if (data->args[i].token == PIPE)
				i++;
			while (data->args[i].token != WORD)
				i += 2;
			data->arglst[k].args[j] = ft_strdup(data->args[i].s);
			i++;
		}
		if (i < data->arg_count && data->args[i].token != PIPE)
			i += 2;
		data->arglst[k].args[j] = NULL;
	}
}

void	arglst_generator(t_data *data)
{
	int	i;

	i = 0;
	data->cmd_count = 1;
	while (++i < data->arg_count)
		if (data->args[i].token == PIPE)
			data->cmd_count++;
	data->arglst = (t_arglst *)malloc(sizeof(t_arglst) * (data->cmd_count + 1));
	if (!data)
		return ;
	i = -1;
	while (++i <= data->cmd_count)
	{
		data->arglst[i].args = NULL;
		data->arglst[i].in = NULL;
		data->arglst[i].out = NULL;
		data->arglst[i].lmt = NULL;
		data->arglst[i].append = FALSE;
	}
	assignment_arglst(data);
}
