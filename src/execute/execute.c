/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:04:27 by tmidik            #+#    #+#             */
/*   Updated: 2025/05/13 20:09:01 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_built_in(char *function_name)
{
	if (ft_strcmp(function_name, "echo") == 0)
		return 1;
	else if (ft_strcmp(function_name, "cd") == 0)
		return 1;
	else if (ft_strcmp(function_name, "pwd") == 0)
		return 1;
	else if (ft_strcmp(function_name, "export") == 0)
		return 1;
	else if (ft_strcmp(function_name, "unset") == 0)
		return 1;
	else if (ft_strcmp(function_name, "env") == 0)
		return 1;
	else if(ft_strcmp(function_name, "exit") == 0)
		return 1;
	else
		return (0);
}

int	execute(t_data *data)
{
	pid_t	pid;
	char	*path;
	
	if (is_built_in(data->args[0]))
		return 1;
	pid = fork();
	if (pid == 0)
	{
		path = get_command_path(data->args[0], data->envp);
		if (!path)
			(perror("Command not found!"), exit(EXIT_FAILURE));
		execve(path, data->args, data->envp);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
	return (0);
}