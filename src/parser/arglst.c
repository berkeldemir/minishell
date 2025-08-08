/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:38:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/08 12:21:44 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	assigning(t_data *data, int i, int k, int j)
{
	if (i < data->arg_count && data->args[i].token == PIPE)
		i++;
	while (i < data->arg_count && data->args[i].token != WORD)
		i += 2;
	if (i < data->arg_count)
		data->arglst[k].args[j] = ft_strdup(data->args[i].s);
	else
		data->arglst[k].args[j] = NULL;
	i++;
}

int	assignment_arglst(t_data *data)
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
		data->arglst[k].args = (char **)malloc(sizeof(char *) * (limit + 1));
		if (!data->arglst[k].args)
			return (0);
		if (limit == 0)
			data->arglst[k].args[0] = NULL;
		j = -1;
		while (++j < limit)
			assigning(data, i, k, j);
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
	data->heredoc_fine = TRUE;
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
