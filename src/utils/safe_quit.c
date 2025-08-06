/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:19:41 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/06 14:39:18 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	safe_free(void **ptr)
{
	if (!ptr || !*ptr)
		return ;
	else
		free(*ptr);
	*ptr = NULL;
}

void	free_env(t_data *data, t_bool free_all)
{
	int	i;
	t_env *tmp;

	while (free_all == TRUE && data->env)
	{
		safe_free((void *)&data->env->key);
		safe_free((void *)&data->env->value);
		tmp = data->env;
		data->env = data->env->next;
		safe_free((void *)&tmp);
	}
	if (free_all == TRUE && data->env)
		safe_free((void *)&data->env);
	i = -1;
	while (data->curr_env && data->curr_env[++i] != NULL)
		safe_free((void *)&data->curr_env[i]);
	safe_free((void *)&data->curr_env);
}

void	free_args(t_data *data)
{
	int	i;
	int	j;

	if (data->arglst)
	{
		i = -1;
		while (++i < data->cmd_count)
		{
			j = -1;
			while (data->arglst[i].args[++j])
				safe_free((void *)&data->arglst[i].args[j]);
			safe_free((void *)&data->arglst[i]);
			safe_free((void *)&data->arglst[i].in);
			safe_free((void *)&data->arglst[i].out);
			safe_free((void *)&data->arglst[i].lmt);
		}
		safe_free((void *)&data->arglst);
	}
	if (data->args)
	{
		i = -1;
		while (++i < data->arg_count)
			safe_free((void *)&data->args[i].s);
		safe_free((void *)&data->args);
	}
}

void	safe_quit(t_data *data, char **extra, int max)
{
	int		i;

	i = -1;
	if (extra)
		while (++i < max)
			safe_free((void *)&extra[i]);
	safe_free((void *)&data->fds);
	safe_free((void *)&data->program_name);
	free_env(data, TRUE);
	free_args(data);
	safe_free((void *)&data);
}
