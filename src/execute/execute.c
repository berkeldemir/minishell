/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:44:26 by tmidik            #+#    #+#             */
/*   Updated: 2025/07/29 12:42:44 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_built_in(t_data *data, char **args)
{
	if (ms_ft_strcmp(data->args[0].s, "echo")  == 0)
		return (ft_echo(data, args), 1);
	else if (ms_ft_strcmp(data->args[0].s, "cd")  == 0)
		return (ft_cd(data, args), 1);
	else if (ms_ft_strcmp(data->args[0].s, "pwd")  == 0)
		return (ft_pwd(args), 1);
	else if (ms_ft_strcmp(data->args[0].s, "export")  == 0)
		return (ft_export(data, args), 1);
	else if (ms_ft_strcmp(data->args[0].s, "unset")  == 0)
		return (ft_unset(data, args[1], args), 1);
	else if (ms_ft_strcmp(data->args[0].s, "env")  == 0)
		return (ft_env(data), 1);
	else if (ms_ft_strcmp(data->args[0].s, "exit")  == 0)
		return (ft_exit(args), 1);
	else
		return (0);
}

/*static char	**args_converter(t_data *data, int i)
{
	int j;
	
	j = 0;
	while (data->arglst[i].args[j] != NULL)
		j++;
	char **ret = malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (data->arglst[i].args[j] != NULL)
	{
		ret[j] = data->arglst[i].args[j];
		j++;
	}
	ret[j] = NULL;
	return ret;
}*/

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
	(free(*path), perror("command not found"), exit(EXIT_FAILURE));
}

static void	link_pipe_ends_and_redirs(t_data *data, int i)
{
	int	j;
	int	fd;

	if (data->arglst[i].lmt)
	{
		launch_heredoc(data, i);
		data->arglst[i].in = TMPFILE;
	}
	if (data->arglst[i].in)
	{
		fd = open(data->arglst[i].in, O_RDONLY);
		if (fd < 0)
			(perror("open infile"), exit(1));
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (i > 0)
    	dup2(data->fds[(i - 1) * 2], STDIN_FILENO);
	if (data->arglst[i].out)
	{
		fd = open(data->arglst[i].out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			(perror("open outfile"), exit(1));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (i < data->cmd_count - 1)
		dup2(data->fds[(i * 2) + 1], STDOUT_FILENO);
	j = 0;
	while (j < 2 * (data->cmd_count - 1))
		close(data->fds[j++]);
	//free(data->fds);
}

static void	close_all(t_data *data)
{
	int	j;

	j = -1;
	while (++j < 2 * (data->cmd_count - 1))
		close(data->fds[j]);
}

static void	child_process(t_data *data, int i)
{
	char	*path;
	char	**env;

	signal(SIGINT, SIG_DFL);
	link_pipe_ends_and_redirs(data, i);
	if (is_built_in(data, data->arglst[i].args))
		exit(EXIT_SUCCESS);
	path = get_command_path(data->arglst[i].args[0], data);
	if (!path)
		handle_path_not_found(&path, data->arglst[i].args);
	env = env_converter(data);
	execve(path, data->arglst[i].args, env);
	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
	(free(path), perror("execve"), exit(EXIT_FAILURE));
}

int	executor(t_data *data, char **env)
{
	pid_t	pid;
	int		i;
	int		status;

	data->stdin_dup = dup(STDIN_FILENO);
	data->stdout_dup = dup(STDOUT_FILENO);
	if (data->cmd_count == 1 && is_built_in(data, data->arglst[0].args))
		return (1);
	i = -1;
	while (++i < data->cmd_count)
	{
		pid = fork();
		if (pid == 0)
			child_process(data, i);
		else if (pid < 0)
			perror("fork");
	}
	i = -1;
	while (++i < 2 * (data->cmd_count - 1))
		close(data->fds[i]);
	while (wait(&status) > 0)
	(dup2(data->stdin_dup, STDIN_FILENO), close(data->stdin_dup));
	(dup2(data->stdout_dup, STDOUT_FILENO), close(data->stdout_dup));
	unlink(TMPFILE);
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}
