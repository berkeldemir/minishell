/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:40:55 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/19 13:49:02 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_data *data)
{
	char	**current_env;
	int		i;

	current_env = env_converter(data);
	i = -1;
	while (current_env[++i])
		printf("%s\n", current_env[i]);
	return (0);
}