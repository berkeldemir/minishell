/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:41:23 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/20 17:09:47 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_data *data, char *key, char **args)
{
	t_env	*tmp;
	t_env	*prev;

	if (!args[1])
	{
		write(2, "unset: no enough arguments\n", 27);
		return (1);
	}
	tmp = *data->env;
	prev = NULL;
	while (tmp)
	{
		if (ms_ft_strcmp(tmp->key, key) == 0)
		{
			if (prev == NULL)
				*data->env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}
