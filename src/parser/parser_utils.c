/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:17:43 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/07 21:50:38 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	put_inplace(t_data *data, char *str, int *j)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		data->args[data->tmps.arg_i].s[*j] = str[i];
		*j += 1;
	}	
	if (str)
		free(str);
	return (i + 1);
}

int	count_args_helper(char *inp, int *count)
{
	int	i;

	i = 0;
	if (inp[i] && !is_quote(inp[i]) && !is_redir_pipe(inp[i]))
	{
		while (!is_quote(inp[i]) && !is_srp(inp[i]))
			i++;
		if (is_srp(inp[i]) && ++(*count))
			while (is_space(inp[i]))
				i++;
	}
	return (i);
}

int	count_args(char *inp, t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (inp[i])
	{
		data->tmps.quote = inp[i];
		if (is_quote(data->tmps.quote) && ++i)
			while (inp[i] && inp[i] != data->tmps.quote)
				i++;
		if (is_quote(inp[i]) && is_srp(inp[++i]) && ++count)
			while (is_space(inp[i]))
				i++;
		i += count_args_helper(&inp[i], &count);
		if (is_redir_pipe(inp[i]))
			i += count_handle_redir_pipe(&inp[i], &count);
	}
	return (count);
}

int	parser_syntax_checker(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->arg_count)
	{
		if (data->args[i].s && data->args[i].token != WORD)
		{
			if (i + 1 == data->arg_count || data->args[i + 1].token != WORD)
			{
				if (data->args[i].token == PIPE && \
				(data->args[i + 1].token == REDIR_IN || \
				data->args[i + 1].token == REDIR_OUT || \
				data->args[i + 1].token == HEREDOC))
					continue ;
				if (data->args[i + 1].token != HEREDOC)
				{
					write(2, "minishell: syntax error\n", 24);
					exit_code(SET, 2);
					return (2);
				}
			}
		}
	}
	return (0);
}

int	syntax_checker(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (printf("minishell: unclosed quote\n"), 1);
		}
		i++;
	}
	return (0);
}
