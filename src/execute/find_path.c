/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:46:54 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/08 13:30:56 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*converter(char *command, char *path)
{
	char	*temp;
	char	*res_path;

	temp = ft_strjoin("/", path);
	res_path = ft_strjoin(command, temp);
	free(temp);
	return (res_path);
}

char	*get_command_path(char *str, t_data *data)
{
	char	*full_path;
	char	*command_path;
	char	**path_array;
	int		i;

	full_path = get_env_val(data, ft_strdup("PATH"));
	if (!full_path)
		return (NULL);
	path_array = ft_split(full_path, ':');
	if (!path_array)
		return (NULL);
	i = -1;
	while (path_array[++i])
	{
		command_path = converter(str, path_array[i]);
		if (access(command_path, X_OK) == 0)
		{
			free_array(path_array);
			return (command_path);
		}
		free(command_path);
	}
	free_array(path_array);
	return (NULL);
}
