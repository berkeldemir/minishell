/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:34:14 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/08 11:14:12 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir_pipe(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_srp(char c)
{
	if (c == '\0' || is_space(c) || is_redir_pipe(c))
		return (1);
	return (0);
}

int	count_handle_redir_pipe(char *input, int *count)
{
	int	i;

	i = 0;
	if (!is_redir_pipe(input[0]))
		return (0);
	if ((input[i] == '>' && input[i + 1] == '>') || \
	(input[i] == '<' && input[i + 1] == '<'))
		i++;
	i++;
	*count += 1;
	while (is_space(input[i]))
		i++;
	return (i);
}

int	calc_handle_redir_pipe(char *input, int *len, int *i)
{
	int	j;

	j = 0;
	if (is_redir_pipe(input[j]))
	{
		if ((input[j] == '>' && input[j + 1] == '>') || \
		(input[j] == '<' && input[j + 1] == '<'))
			j++;
		j++;
		*len += j;
		*i += j;
		return (j);
	}
	return (0);
}

int	assign_handle_redir_pipe(t_data *data, char *input, int *i, int *j)
{
	if (is_redir_pipe(input[0]))
	{
		if (input[0] == '|')
			data->args[data->tmps.arg_i].token = PIPE;
		if (input[0] == '>')
			data->args[data->tmps.arg_i].token = REDIR_OUT;
		if (input[0] == '<')
			data->args[data->tmps.arg_i].token = REDIR_IN;
		data->args[data->tmps.arg_i].s[*j] = input[0];
		if ((input[0] == '>' || input[0] == '<') && input[1] == input[0])
		{
			if (input[1] == '>')
				data->args[data->tmps.arg_i].token = APPEND;
			if (input[1] == '<')
				data->args[data->tmps.arg_i].token = HEREDOC;
			(*j)++;
			data->args[data->tmps.arg_i].s[*j] = input[1];
			(*i)++;
		}
		(*j)++;
		return (1);
	}
	return (0);
}
