/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:55:53 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/27 19:02:16 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int calc_value_size(t_data *data, char *key)
{
	int i;

	i = 0;
	while (data->envp_copy[i])
}

char	*get_env_value(char **envp, char *key)
{
	int		i;
	char	*command_path;

	i = -1;
	while(envp[++i])
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
			return (envp[i] + 5);
	return (NULL);
}
