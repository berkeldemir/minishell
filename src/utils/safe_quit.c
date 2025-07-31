/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:19:41 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/31 20:30:40 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env(t_data *data, t_bool free_all)
{
	int	i;
	t_env *tmp;

	while (free_all == TRUE && data->env)
	{
		free(data->env->key);
		free(data->env->value);
		tmp = data->env;
		data->env = data->env->next;
		free(tmp);
	}
	if (free_all == TRUE && data->env)
		free(data->env);
	i = -1;
	while (data->curr_env && data->curr_env[++i] != NULL)
		free(data->curr_env[i]);
	if (data->curr_env)
		free(data->curr_env);
}

void	free_args(t_data *data)
{
	int	i;
	int j;

	i = -1;
	while (++i < data->cmd_count)
	{
		j = -1;
		while (data->arglst[i].args[++j])
		{
			free(data->arglst[i].in);
			free(data->arglst[i].out);
			free(data->arglst[i].lmt);
			free(data->arglst[i].args[j]);
		}
		free(data->arglst[i].args);
		/*if (data->arglst->in)
			free(data->arglst->in);
		if (data->arglst->out)

		if (data->arglst->lmt)
		*/
	}
	free(data->arglst);
	i = -1;
	while (++i < data->arg_count)
		free(data->args[i].s);
	free(data->args);
}


void	safe_quit(t_data *data, char **extra, int max)
{
	int		i;

	i = -1;
	if (extra)
		while (++i < max)
			free(extra[i]);
	if (data->fds)
		free(data->fds);
	if (data->program_name)
		free(data->program_name);
	free_env(data, TRUE);
	free_args(data);
	free(data);
}
