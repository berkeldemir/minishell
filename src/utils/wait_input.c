/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:19:42 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/08 12:40:31 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	print_prompt(t_data *data)
{
	data->input = readline("\033[38;2;175;252;65mMINISHELL>₺ \033[0m");
	if (!data->input)
	{
		write(1, "exit\n", 5);
		free_env(data, TRUE);
		safe_free((void *)&data->name);
		return (1);
	}
	return (0);
}

static int	assign_pipes(t_data *data)
{
	int	i;

	data->fds = malloc((2 * (data->cmd_count - 1)) * sizeof(int));
	if (!data->fds)
		return (1);
	i = -1;
	while (++i < data->cmd_count - 1)
		if (pipe(&data->fds[i * 2]) == -1)
			return (perror("pipe"), 1);
	return (0);
}

static int	parse_part(t_data *data)
{
	add_history(data->input);
	if (syntax_checker(data->input) != 0 || parser(data) != 0)
	{
		free_args(data);
		free(data->input);
		return (1);
	}
	arglst_generator(data);
	if (!data->arglst || !data->arglst[0].args || \
	(!data->arglst[0].args[0] && (!data->arglst[0].lmt && \
	!data->arglst[0].in && !data->arglst[0].out)) || \
	assign_pipes(data) != 0)
	{
		free_args(data);
		free(data->input);
		exit_code(SET, 1);
		return (1);
	}
	return (0);
}

void	wait_input(t_data *data)
{
	char	path[1023];

	while (1)
	{
		(signal(SIGQUIT, SIG_IGN), signal(SIGINT, handle_sigint_parent));
		if (getcwd(path, sizeof(path)) == NULL)
			return ;
		if (print_prompt(data) != 0)
			break ;
		if (data->input[0] != '\0')
		{
			if (parse_part(data) != 0)
				continue ;
			data->curr_env = env_converter(data);
			if (data->heredoc_fine == TRUE)
				exit_code(SET, executor(data));
			(free_args(data), free_env(data, FALSE));
			safe_free((void *)&data->fds);
		}
		free(data->input);
	}
}
