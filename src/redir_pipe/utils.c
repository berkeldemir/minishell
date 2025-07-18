/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:38:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/18 12:46:32 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_size_arg_converter(t_args *args, int start, int total)
{
	int	i;
	int	count;

	count = 0;
	i = start - 1;
	while (++i < total && args[i].token != PIPE)
		count++;
	return (count);
}

static void	assignment_arg_converter(t_data *data)
{
	int	limit;
	int	i;
	int	j;
	int	k;

	i = -1;
	k = -1;
	while (++k >= 0 && ++i < data->arg_count && k < data->cmd_count)
	{
		limit = find_size_arg_converter(data->args, i, data->arg_count);
		data->args_tmp[k] = (t_args *)malloc(sizeof(t_args) * (limit + 1));
		j = -1;
		while (++j < limit)
		{
			data->args_tmp[k][j].s = ft_strdup(data->args[i].s);
			printf("k:%i\tj:%i\ti:%i\t%s\n", k, j, i, data->args_tmp[k][j].s);
			data->args_tmp[k][j].token = data->args[i++].token;
			data->args_tmp[k][j].index = j;
			//free(data->args[i].s);
		}
		data->args_tmp[k][j].s = NULL;
	}
	data->args_tmp[k] = NULL;
	//free(data->args);
}

void	arg_converter(t_data *data)
{
	int	i;

	i = 0;
	data->cmd_count = 1;
	while (++i < data->arg_count)
		if (data->args[i].token == PIPE)
			data->cmd_count++;
	data->args_tmp = (t_args **)malloc(sizeof(t_args *) * (data->cmd_count + 1));
	if (!data)
		return ;
	assignment_arg_converter(data);
}
