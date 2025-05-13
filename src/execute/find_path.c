/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:30:38 by tmidik            #+#    #+#             */
/*   Updated: 2025/05/13 20:36:03 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *converter(char *command, char *path)
{
	char	*temp;
	char	*res_path;

	temp = ft_strjoin("/", path);
	res_path = ft_strjoin(command, temp);
	free(temp);
	return (res_path);
}

static char	*get_env_key(char **envp)
{
	int		i;
	char	*command_path;

	i = -1;
	while(envp[++i])
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
	return (NULL);
}

char	*get_command_path(char *str, char **envp)
{
	char	*full_path;
	char	*command_path;
	char	**path_array;
	int		i;

	full_path = get_env_key(envp);
	printf("PATH :%s", full_path);
	path_array = ft_split(full_path, ':');
	i = -1;
	while (path_array[++i])
	{
		command_path = converter(str, path_array[i]);
		if (access(command_path, X_OK) == 0)
			return (command_path);
	}
	free_array(path_array);
	return (NULL);
}
