/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:41:23 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/05 17:57:01 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_data *data, char *key, char **args)
{
	t_env	*tmp;
	t_env	*prev;

	if (!args[1])
		return (0);
	tmp = data->env;
	prev = NULL;
	while (tmp)
	{
		if (ms_ft_strcmp(tmp->key, key) == 0)
		{
			if (prev == NULL)
				data->env = tmp->next;
			else
				prev->next = tmp->next;
			return (free(tmp->key), free(tmp->value), free(tmp), 0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}
