/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:07:00 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/08 12:40:13 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_code(char c, int value)
{
	static int	code = 0;

	if (c == GET)
	{
		(void)value;
		return (code);
	}
	else if (c == SET)
		code = value;
	return (0);
}

void	handle_sigint_parent(int sig)
{
	(void)sig;
	exit_code(SET, 130);
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_child(int sig)
{
	(void)sig;
	exit_code(SET, 130);
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	exit_code(SET, 131);
	write(2, "Quit (core dumped)\n", 19);
	signal(SIGQUIT, SIG_IGN);
	kill(getpid(), SIGQUIT);
}

void	handle_sig_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	safe_quit(env_data(GET, NULL), NULL, 0);
	exit(130);
}
