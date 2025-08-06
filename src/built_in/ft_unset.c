/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:41:23 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/06 19:51:38 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	explore_and_unset(t_data *data, char **args, int i)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = data->env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, args[i]) == 0)
		{
			if (prev == NULL)
				data->env = tmp->next;
			else
				prev->next = tmp->next;
			(free(tmp->key), free(tmp->value), free(tmp));
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_data *data, char **args)
{
	int		i;

	if (!args[1])
		return (0);
	i = 0;
	while (args[++i])
		explore_and_unset(data, args, i);
	return (0);
}
