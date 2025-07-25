/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:38:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/25 13:24:40 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_redirs_arglst(t_data *data, int i, int k)
{
	if (data->args[i].token == APPEND || data->args[i].token == REDIR_OUT)
		data->arglst[k].out = ft_strdup(data->args[i + 1].s);
	else if (data->args[i].token == REDIR_IN)
		data->arglst[k].in = ft_strdup(data->args[i + 1].s);
	else if (data->args[i].token == HEREDOC)
		data->arglst[k].lmt = ft_strdup(data->args[i + 1].s);
	if (data->args[i].token == APPEND)
		data->arglst[k].append = TRUE;
	free(data->args[i + 1].s);
	return (1);
}

static int	find_size_arglst(t_data *data, int start, int total, int k)
{
	int	i;
	int	count;

	count = 0;
	i = start - 1;
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
		limit = find_size_arglst(data, i, data->arg_count, k);
		/*if (data->arglst[k].in)
			printf("k:%i\tin:%s\n", k, data->arglst[k].in);
		if (data->arglst[k].out)
			printf("k:%i\tout:%s\n", k, data->arglst[k].out);
		if (data->arglst[k].lmt)
			printf("k:%i\tlmt:%s\n", k, data->arglst[k].lmt);
		if (data->arglst[k].append == TRUE)
			printf("k:%i\tappend:%i\n", k, data->arglst[k].append);*/
		data->arglst[k].args = (char **)malloc(sizeof(char *) * (limit + 1));
		j = -1;
		while (++j < limit)
		{
			while (data->args[i].token != WORD)
				i += 2;
			data->arglst[k].args[j] = ft_strdup(data->args[i].s);
			//printf("k:%i\targs[%i]:%s\n", k, j, data->arglst[k].args[j]);
			free(data->args[i].s);
			i++;
		}
		data->arglst[k].args[j] = NULL;
	}
	//free(data->args);
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
		data->arglst[i].append = FALSE;
	}
	assignment_arglst(data);
}
