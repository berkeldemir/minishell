/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:19:41 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/30 14:51:48 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	safe_quit(t_data *data, char **extra)
{
	int	i;

	i = -1;
	if (extra)
		while (extra[++i])
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
		data->env = data->env->next;
	}
	
	free(data->env);
	free(data);
}
