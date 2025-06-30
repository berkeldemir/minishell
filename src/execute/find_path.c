/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:46:54 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/29 14:48:52 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *converter(char *command, char *path)
{
	char	*temp;
	char	*res_path;

	temp = ms_ft_strjoin("/", path);
	res_path = ms_ft_strjoin(command, temp);
	free(temp);
	return (res_path);
}

char	*get_command_path(char *str, t_data *data)
{
	char	*full_path;
	char	*command_path;
	char	**path_array;
	int		i;

	full_path = get_env_val(data, "PATH");
	/*if (!full_path)
		full_path = "/bin:/usr/bin"; // fallback*/
	//printf("DEBUG: PATH -> %s\n", full_path);
	path_array = ft_split(full_path, ':');
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
