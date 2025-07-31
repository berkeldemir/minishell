/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:44:26 by tmidik            #+#    #+#             */
/*   Updated: 2025/07/31 21:02:20 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_built_in(t_data *data, char **args, int *retval)
{
	*retval = 0;
	
	if (data->cmd_count == 1 && (!ms_ft_strcmp(args[0], "echo") || \
	!ms_ft_strcmp(args[0], "cd") || !ms_ft_strcmp(args[0], "pwd") || \
	!ms_ft_strcmp(args[0], "export") || !ms_ft_strcmp(args[0], "unset") || \
	!ms_ft_strcmp(args[0], "env") || !ms_ft_strcmp(args[0], "exit")))
		link_pipe_ends_and_redirs(data, 0);
	if (ms_ft_strcmp(args[0], "echo")  == 0)
		*retval = ft_echo(data, args);
	else if (ms_ft_strcmp(args[0], "cd")  == 0)
		*retval = ft_cd(data, args);
	else if (ms_ft_strcmp(args[0], "pwd")  == 0)
		*retval = ft_pwd();
	else if (ms_ft_strcmp(args[0], "export")  == 0)
		*retval = ft_export(data, args);
	else if (ms_ft_strcmp(args[0], "unset")  == 0)
		*retval = ft_unset(data, args[1], args);
	else if (ms_ft_strcmp(args[0], "env")  == 0)
		*retval = ft_env(data);
	else if (ms_ft_strcmp(args[0], "exit")  == 0)
		*retval = ft_exit(data, args);
	else
		return ((*retval) = 0 & 0);
	(dup2(data->stdin_dup, STDIN_FILENO), close(data->stdin_dup));
	return (dup2(data->stdout_dup, STDOUT_FILENO), close(data->stdout_dup), 1);
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

void	link_pipe_ends_and_redirs(t_data *data, int i)
{
	int	fd;

	if (data->arglst[i].lmt)
		launch_heredoc(data, i);
	if (data->arglst[i].in)
	{
		fd = open(data->arglst[i].in, O_RDONLY);
		if (fd < 0)
			(perror("open infile"), safe_quit(data, NULL, 0), exit(1));
		(dup2(fd, STDIN_FILENO), close(fd));
	}
	else if (i > 0)
    	dup2(data->fds[(i - 1) * 2], STDIN_FILENO);
	if (data->arglst[i].out)
	{
		fd = open(data->arglst[i].out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			(perror("open outfile"), safe_quit(data, NULL, 0), exit(1));
		(dup2(fd, STDOUT_FILENO), close(fd));
	}
	else if (i < data->cmd_count - 1)
		dup2(data->fds[(i * 2) + 1], STDOUT_FILENO);
	i = 0;
	while (i < 2 * (data->cmd_count - 1))
		close(data->fds[i++]);
}

static void	child_process(t_data *data, int i)
{
	char	*path;
	int		retval;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	link_pipe_ends_and_redirs(data, i);
	if (is_built_in(data, data->arglst[i].args, &retval))
		(safe_quit(data, NULL, 0), exit(retval));
	path = get_command_path(data->arglst[i].args[0], data);
	if (!path)
		handle_path_not_found(data, &path, data->arglst[i].args);
	execve(path, data->arglst[i].args, data->curr_env);
	(free(path), perror("execve"), safe_quit(data, NULL, 0), exit(0));
}

int	executor(t_data *data)
{
	pid_t	pid;
	int		i;
	int		status;
	int		rv;

	data->stdin_dup = dup(STDIN_FILENO);
	data->stdout_dup = dup(STDOUT_FILENO);
	if (data->cmd_count == 1 && is_built_in(data, data->arglst[0].args, &rv))
		return (rv);
	signal(SIGQUIT, handle_sigquit);
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
