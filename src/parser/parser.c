/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:18:36 by beldemir          #+#    #+#             */
/*   Updated: 2025/06/14 17:21:24 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	assign_arg_helper(t_data *data, char *input, int *j)
{
	int		i;
	char	*val;

	if (input[0] == '$')
	{
		i = 1;
		if (data->tmps.quote == '\'')
			return (0);
		if ((input[i] <= '9' && input[i] >= '0') || input[i] == '#')
		{
			if (input[i] == '0')
				return (put_value_in_place(data, data->program_name, *j));
			if (input[i] == '#')
				return (put_value_in_place(data, "0", *j));
		}
		while ((input[i] >= 'A' && input[i] <= 'Z') || \
		(input[i] >= 'a' && input[i] <= 'z') || \
		(input[i] >= '0' && input[i] <= '9') || input[i] == '_')
			i++;
		val = get_env_val(data, ft_substr(&input[1], 0, i));
		return (put_value_in_place(data, val, *j));
	}
	data->args[data->tmps.arg_i].s[*j] = *input;
	*j += 1;
	return (1);
}

static void	assign_arg(t_data *data, char *input)
{
	int		i;
	int		j;

	data->args[data->tmps.arg_i].s = (char *)malloc(data->tmps.len + 1);
	if (!data->args[data->tmps.arg_i].s)
		return ;
	i = 0;
	j = 0;
	while (input[i])
	{
		data->tmps.quote = input[i];
		if (is_quote(data->tmps.quote) && ++i)
			while (input[i] && input[i] != data->tmps.quote)
					i += assign_arg_helper(data, &input[i], &j);
		if (is_quote(input[i]) && is_space(input[++i]))
			break ;
		if (input[i] && !is_quote(input[i]))
			while (input[i] && !is_quote(input[i]) && !is_space(input[i]))
					i += assign_arg_helper(data, &input[i], &j);
		if (is_space(input[i]))
			break ;
	}
	data->args[data->tmps.arg_i].s[j] = '\0';
}

static int	calc_env_var_len(t_data *data, char *input)
{
	int		i;
	char	*val;

	i = 0;
	if (data->tmps.quote == '\'')
		return (++(data->tmps.len) && 1);
	if ((input[i] <= '9' && input[i] >= '0') || input[i] == '#')
	{
		if (input[i] == '0')
			data->tmps.len += ft_strlen(data->program_name);
		if (input[i] == '#')
			data->tmps.len += 1;
		return (i);
	}
	while ((input[i] >= 'A' && input[i] <= 'Z') || \
	(input[i] >= 'a' && input[i] <= 'z') || \
	(input[i] >= '0' && input[i] <= '9') || input[i] == '_')
		i++;
	val = get_env_val(data, ft_substr(&input[1], 0, i));
	data->tmps.len += ft_strlen(val);
	free(val);
	return (i);
}

static int	calc_arg_len(t_data *data, char *input)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	printf("Input: %s\n", input);
	while (input[i])
	{
		data->tmps.quote = input[i];
		if (is_quote(data->tmps.quote))
			while (input[++i] && input[i] != data->tmps.quote && ++len)
				if (input[i] == '$' && len--)
					i += calc_env_var_len(data, &input[i]);
		if (is_quote(input[i]) && is_space(input[++i]))
			break ;
		if (input[i] && !is_quote(input[i]))
			while (input[i] && !is_quote(input[i]) && !is_space(input[i]) && \
			++i && ++len)
				if (input[i] == '$' && len--)
					i += calc_env_var_len(data, &input[i]);
		if (is_space(input[i]))
			break ;
	}
	data->tmps.len = len;	
	printf("Arg Len: %d\n", data->tmps.len);
	return (i);
}

int	parser(t_data *data)
{
	int		i;
	int		j;

	data->arg_count = count_args(data->input, data);
	printf("Arg Count: %d\n", data->arg_count);
	data->args = malloc(sizeof(char *) * (data->arg_count + 1));
	if (!data->args)
		return (1);
	i = 0;
	data->tmps.len = 0;
	data->tmps.arg_i = 0;
	while (data->input[i])
	{
		data->tmps.quote = '\0';
		while (data->input[i] && is_space(data->input[i]))
			i++;
		if (data->input[i])
		{
			j = calc_arg_len(data, &data->input[i]);
			assign_arg(data, &data->input[i]);
			data->tmps.arg_i++;
			i += j;
		}
	}
	return (0);
}
