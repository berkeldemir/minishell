/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:41:23 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/19 16:44:08 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_data *data, char *key)
{
	t_env	*tmp;
	t_env	*prev;

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
