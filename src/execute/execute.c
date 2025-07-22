/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:44:26 by tmidik            #+#    #+#             */
/*   Updated: 2025/07/22 14:26:17 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_built_in(t_data *data, char **args)
{
	if (ms_ft_strcmp(data->args[0].s, "echo") == 0)
		return (ft_echo(data, args), 1);
	else if (ms_ft_strcmp(data->args[0].s, "cd") == 0)
		return (ft_cd(data, args), 1);
	else if (ms_ft_strcmp(data->args[0].s, "pwd") == 0)
		return (ft_pwd(args), 1);
	else if (ms_ft_strcmp(data->args[0].s, "export") == 0)
		return (ft_export(data, args), 1);
	else if (ms_ft_strcmp(data->args[0].s, "unset") == 0)
		return (ft_unset(data, args[1], args), 1);
	else if (ms_ft_strcmp(data->args[0].s, "env") == 0)
		return (ft_env(data), 1);
	else if (ms_ft_strcmp(data->args[0].s, "exit") == 0)
		return (ft_exit(args), 1);
	else
		return (0);
}

static char	**args_converter(t_data *data, int i)
{
	char	**ret;
	int		j;

	ret = malloc(sizeof(char *) * (data->arg_count + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (j < data->arg_count)
	{
		ret[j] = data->arglst[i][j].s;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

void	handle_path_not_found(char **path, char **args)
{
	int	i;

	i = 0;
	while (args[0][i])
	{
		if (args[0][i] == '/')
		{
			*path = ft_strdup(args[0]);
			return ;
		}
		i++;
	}
	(perror("command not found!"), exit(EXIT_FAILURE));
}

int	execute(t_data *data, int i, char **current_env)
{
	pid_t	pid;
	char	*path;
	char	**args;

	args = args_converter(data, i);
	if (is_built_in(data, args))
		return (0);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		path = get_command_path(args[0], data);
		if (!path)
			handle_path_not_found(&path, args);
		execve(path, args, current_env);
		(perror("minishell"), exit(EXIT_FAILURE));
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, NULL, 0);
		signal(SIGINT, handle_sigint);
	}
	return (0);
}
