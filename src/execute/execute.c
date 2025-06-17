/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:44:26 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/17 17:18:18 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_built_in(char *function_name)
{
	if (ms_ft_strcmp(function_name, "echo") == 0)
		return 1;
	else if (ms_ft_strcmp(function_name, "cd") == 0)
		return 1;
	else if (ms_ft_strcmp(function_name, "pwd") == 0)
		return 1;
	else if (ms_ft_strcmp(function_name, "export") == 0)
		return 1;
	else if (ms_ft_strcmp(function_name, "unset") == 0)
		return 1;
	else if (ms_ft_strcmp(function_name, "env") == 0)
		return 1;
	else if(ms_ft_strcmp(function_name, "exit") == 0)
		return 1;
	else
		return (0);
}

static char **args_converter(t_data *data)
{
	char **argv;
	int i;

	argv = malloc(sizeof(char *) * (data->arg_count + 1));
	if (!argv)
		return NULL;
	i = 0;
	while (i < data->arg_count)
	{
		argv[i] = data->args[i].s;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

int	execute(t_data *data)
{
	pid_t	pid;
	char	*path;
	char	**current_env;
	char	**args;

	current_env = env_converter(data);
	args = args_converter(data);
	if (is_built_in(args[0]))
		return (1);
	pid = fork();
	if (pid == 0)
	{
		path = get_command_path(args[0], data);
		if (!path)
			(perror("command not found!"), exit(EXIT_FAILURE));
		execve(path, args,current_env);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
	return (0);
}