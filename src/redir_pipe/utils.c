/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:38:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/19 12:14:55 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_size_arglst(t_args *args, int start, int total)
{
	int	i;
	int	count;

	count = 0;
	i = start - 1;
	while (++i < total && args[i].token != PIPE)
		count++;
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
		limit = find_size_arglst(data->args, i, data->arg_count);
		data->arglst[k] = (t_args *)malloc(sizeof(t_args) * (limit + 1));
		j = -1;
		while (++j < limit)
		{
			data->arglst[k][j].s = ft_strdup(data->args[i].s);
			printf("k:%i\tj:%i\ti:%i\t%s\n", k, j, i, data->arglst[k][j].s);
			data->arglst[k][j].token = data->args[i++].token;
			data->arglst[k][j].index = j;
			//free(data->args[i].s);
		}
		data->arglst[k][j].s = NULL;
	}
	data->arglst[k] = NULL;
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
	data->arglst = (t_args **)malloc(sizeof(t_args *) * (data->cmd_count + 1));
	if (!data)
		return ;
	assignment_arglst(data);
}
