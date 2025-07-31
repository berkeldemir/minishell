/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:19:41 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/31 12:06:53 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	safe_quit(t_data *data, char **extra, int max)
{
	int		i;
	int		j;
	t_env *tmp;

	i = -1;
	if (extra)
		while (++i < max)
			free(extra[i]);
	if (data->fds)
		free(data->fds);
	if (data->program_name)
		free(data->program_name);
	i = -1;
	while (data->env)
	{
		free(data->env->key);
		free(data->env->value);
		tmp = data->env;
		data->env = data->env->next;
		free(tmp);
	}
	if (data->env)
		free(data->env);
	i = -1;
	while (++i < data->cmd_count)
	{
		j = -1;
		while (data->arglst[i].args[++j])
			free(data->arglst[i].args[j]);
		free(data->arglst[i].args);
		if (data->arglst->in)
			free(data->arglst->in);
		if (data->arglst->out)
			free(data->arglst->out);
		if (data->arglst->lmt)
			free(data->arglst->lmt);
	}
	free(data->arglst);
	i = -1;
	while (++i < data->arg_count)
		free(data->args[i].s);
	free(data->args);
	i = -1;
	while (data->curr_env && data->curr_env[++i])
		free(data->curr_env[i]);
	if (data->curr_env)
		free(data->curr_env);
	free(data);
}
