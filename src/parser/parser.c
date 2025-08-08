/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:18:36 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/08 14:03:29 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	assign_arg_helper(t_data *data, char *in, int *j, int flag)
{
	int		i;
	char	*val;

	if (in[0] == '$' && ((flag == 1 && data->tmps.quote != '\'') || \
	flag == 0))
	{
		i = 1;
		if (in[i] == ' ' || !in[i] || in[i] == data->tmps.quote)
			return (put_inplace(data, ft_strdup("$"), j), 1);
		if (!is_alnum(in[i]) && in[i] != '_' && in[i] != '?' && \
		(in[i] > '9' || in[i] < '0'))
			return (put_inplace(data, ft_strdup("$"), j), 1);
		if (in[i] == '0')
			return (put_inplace(data, ft_strdup(data->name), j), ++i);
		if (in[i] == '?')
			return (put_inplace(data, ft_itoa(exit_code(GET, 0)), j), ++i);
		while (is_alnum(in[i]) || in[i] == '_')
			i++;
		val = get_env_val(data, ft_substr(&in[1], 0, i - 1));
		if (!val)
			return (i);
		return (put_inplace(data, ft_strdup(val), j), i);
	}
	data->args[data->tmps.arg_i].s[*j] = *in;
	return (++(*j), 1);
}

static void	assign_arg(t_data *data, char *in)
{
	int		i;
	int		j;

	data->args[data->tmps.arg_i].s = (char *)malloc(data->tmps.len + 1);
	if (!data->args[data->tmps.arg_i].s)
		return ;
	i = 0;
	j = 0;
	while (in[i])
	{
		data->tmps.quote = in[i];
		if (is_quote(data->tmps.quote) && ++i)
			while (in[i] && in[i] != data->tmps.quote)
				i += assign_arg_helper(data, &in[i], &j, 1);
		if (is_quote(in[i]) && is_srp(in[++i]))
			break ;
		if (assign_handle_redir_pipe(data, &in[i], &i, &j))
			break ;
		if (in[i] && !is_quote(in[i]) && !is_redir_pipe(in[i]))
			while (i < ft_strlen(in) && !is_srp(in[i]) && !is_quote(in[i]))
				i += assign_arg_helper(data, &in[i], &j, 0);
		if (in[i] && is_srp(in[i]))
			break ;
	}
	data->args[data->tmps.arg_i].s[j] = '\0';
}

static int	calc_env_var_len(t_data *data, char *in, int *len, int quote)
{
	int		i;
	char	*val;

	i = 0;
	if (quote == 1 && data->tmps.quote == '\'')
		return (++(*len), 0);
	if ((in[i] <= '9' && in[i] >= '0') || in[i] == '?' || in[i] == ' ' \
	|| in[i] == '\0' || (in[i] == data->tmps.quote && in[i] == '\"'))
	{
		if (in[i] == '0')
			*len += ft_strlen(data->name);
		else if (in[i] == '?')
			*len += safe_strlen(ft_itoa(exit_code(GET, 0)));
		else if (in[i] == ' ' || in[i] == '\0' || in[i] == data->tmps.quote)
			*len += 1;
		return (1);
	}
	if (!is_alnum(in[i]) && in[i] != '_')
		return (((*len) += 2), 0);
	while (is_alnum(in[i]) || in[i] == '_')
		i++;
	val = get_env_val(data, ft_substr(&in[0], 0, i));
	if (val)
		*len += ft_strlen(val);
	return (i - 1);
}

static int	calc_arg_len(t_data *data, char *in)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (i < ft_strlen(in))
	{
		data->tmps.quote = in[i];
		if (is_quote(data->tmps.quote))
			while (++i <= ft_strlen(in) && in[i] != data->tmps.quote && ++len)
				if (in[i - 1] == '$' && len--)
					i += calc_env_var_len(data, &in[i], &len, 1);
		if (is_quote(in[i]) && (i == ft_strlen(in) || (is_srp(in[++i]))))
			break ;
		if (calc_handle_redir_pipe(&in[i], &len, &i))
			break ;
		if (in[i] && !is_quote(in[i]) && !is_redir_pipe(in[i]))
			while (i <= ft_strlen(in) && !is_srp(in[i]) && !is_quote(in[i]))
				if (++len && ++i && in[i - 1] == '$' && len--)
					i += calc_env_var_len(data, &in[i], &len, 0) + 1;
		if (i <= ft_strlen(in) && is_srp(in[i]))
			break ;
	}
	data->tmps.len = len;
	return (i);
}

int	parser(t_data *data)
{
	int		i;
	int		j;

	data->arg_count = count_args(data->input, data);
	data->args = malloc(sizeof(t_args) * (data->arg_count + 1));
	if (!data->args)
		return (1);
	i = 0;
	data->tmps.len = 0;
	data->tmps.arg_i = 0;
	while (i < ft_strlen(data->input))
	{
		data->tmps.quote = '\0';
		while (data->input[i] && is_space(data->input[i]))
			i++;
		if (data->input[i])
		{
			j = calc_arg_len(data, &data->input[i]);
			data->args[data->tmps.arg_i].token = WORD;
			assign_arg(data, &data->input[i]);
			data->tmps.arg_i++;
			i += j;
		}
	}
	return (parser_syntax_checker(data));
}
