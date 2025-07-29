/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:17:43 by tmidik            #+#    #+#             */
/*   Updated: 2025/07/29 10:03:05 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	put_value_in_place(t_data *data, char *str, int *j)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		data->args[data->tmps.arg_i].s[*j] = str[i];
		*j += 1;
	}
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
			//printf("\ni:%i\tnext-token:%c\n", i, data->args[i + 1].token);
			if (i + 1 == data->arg_count || data->args[i + 1].token != WORD)
			{
				printf("minishell: syntax error near %s\n", data->args[i].s);
				return (1);
			}
		}
	}
	return (0);
}

int	syntax_checker(char *input)
{
	int	i;
	int	squote_count;
	int	dquote_count;

	squote_count = 0;
	dquote_count = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
			squote_count++;
		if (input[i] == '\"')
			dquote_count++;
	}
	if (squote_count % 2 == 1 || dquote_count % 2 == 1)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (1);
	}
	return (0);
}

/*
int main(void)
{
	t_data *data;
	
	printf("count: %d\n", count_args("  'A\"B'C\"D E\"'F'  \
	'G\"'H\"I'J  K\"L'M  N\"O'P  ", NULL));
	return (0);
}
*/
