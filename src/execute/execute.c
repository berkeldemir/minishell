/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:44:26 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/08 02:44:33 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_built_in(t_data *data, char **args)
{
	exit_code(SET, 0);
	if (data->cmd_count == 1 && (!ft_strcmp(args[0], "echo") || \
	!ft_strcmp(args[0], "cd") || !ft_strcmp(args[0], "pwd") || \
	!ft_strcmp(args[0], "export") || !ft_strcmp(args[0], "unset") || \
	!ft_strcmp(args[0], "env") || !ft_strcmp(args[0], "exit")))
		if (link_pipe_ends_and_redirs(data, 0) != 0)
			return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		exit_code(SET, ft_echo(data, args));
	else if (ft_strcmp(args[0], "cd") == 0)
		exit_code(SET, ft_cd(data, args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		exit_code(SET, ft_pwd(data));
	else if (ft_strcmp(args[0], "export") == 0)
		exit_code(SET, ft_export(data, args));
	else if (ft_strcmp(args[0], "unset") == 0)
		exit_code(SET, ft_unset(data, args));
	else if (ft_strcmp(args[0], "env")  == 0)
		exit_code(SET, ft_env(data));
	else if (ft_strcmp(args[0], "exit") == 0)
		exit_code(SET, ft_exit(data, args));
	else
		return (0);
	(dup2(data->stdin_dup, STDIN_FILENO), close(data->stdin_dup));
	return (dup2(data->stdout_dup, STDOUT_FILENO), close(data->stdout_dup), 1);
}

static void	handle_path_not_found(t_data *data ,char **path, char **args)
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
	(free(*path), safe_quit(data, NULL, 0), write(2, "minishell: command not found\n", 29), exit(127));
}

int	link_pipe_ends_and_redirs(t_data *data, int i)
{
	int	fd;

	if (data->arglst[i].in)
	{
		fd = open(data->arglst[i].in, O_RDONLY);
		if (fd < 0)
			return (perror("open infile"), 1);
		(dup2(fd, STDIN_FILENO), close(fd));
	}
	else if (i > 0)
    	dup2(data->fds[(i - 1) * 2], STDIN_FILENO);
	if (data->arglst[i].out)
	{
		fd = open(data->arglst[i].out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (perror("open outfile"), 1);
		(dup2(fd, STDOUT_FILENO), close(fd));
	}
	else if (i < data->cmd_count - 1)
		dup2(data->fds[(i * 2) + 1], STDOUT_FILENO);
	i = 0;
	while (i < 2 * (data->cmd_count - 1))
		close(data->fds[i++]);
	return (0);
}

static void	child_process(t_data *data, int i)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (link_pipe_ends_and_redirs(data, i) != 0)
		(safe_quit(data, NULL, 0), exit(1));
	if ((data->arglst[i].lmt || data->arglst[i].in || data->arglst[i].out) \
	&& data->arglst[i].args[0] == NULL)
		(safe_quit(data, NULL, 0), exit(0));
	if (is_built_in(data, data->arglst[i].args))
		(safe_quit(data, NULL, 0), exit(exit_code(GET, 0)));
	path = get_command_path(data->arglst[i].args[0], data);
	if (!path)
		handle_path_not_found(data, &path, data->arglst[i].args);
	execve(path, data->arglst[i].args, data->curr_env);
	(free(path), safe_quit(data, NULL, 0));
	if (errno == ENOENT)
		(write(2, "minishell: No such file or directory\n", 37), exit(127));
	else if (errno == EISDIR)
		(write(2, "minishell: Is a directory\n", 26), exit(126));
	else if (errno == EACCES)
		(write(2, "minishell: Permission denied\n", 29), exit(126));
	else
		(perror("minishell"), exit(1));
}

int	executor(t_data *data)
{
	pid_t	pid;
	int		i;
	int		status;

	data->stdin_dup = dup(STDIN_FILENO);
	data->stdout_dup = dup(STDOUT_FILENO);
	if (data->arglst[0].run == TRUE && data->cmd_count == 1 && \
	is_built_in(data, data->arglst[0].args))
		return (exit_code(GET, 0));
	signal(SIGQUIT, handle_sigquit);
	i = -1;
	while (++i < data->cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			if (data->arglst[i].run == TRUE)
				child_process(data, i);
			else
				(safe_quit(data, NULL, 0), exit(1));
		}	
		else if (pid < 0)
			perror("fork");
		if (data->arglst[i].lmt)
			waitpid(pid, &status, 0);
	}
	i = -1;
	while (++i < 2 * (data->cmd_count - 1))
		close(data->fds[i]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code(SET, WEXITSTATUS(status));
	(dup2(data->stdin_dup, STDIN_FILENO), close(data->stdin_dup));
	(dup2(data->stdout_dup, STDOUT_FILENO), close(data->stdout_dup));
	unlink(TMPFILE);
	return (exit_code(GET, 0));
}
