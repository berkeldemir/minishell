/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:40:55 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/04 13:41:05 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_data *data)
{
	int		i;

	i = -1;
	while (data->curr_env[++i])
		if (ft_strlen(ft_strchr(data->curr_env[i], '=')) > 1)
			printf("%s\n", data->curr_env[i]);
	return (0);
}
