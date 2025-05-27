/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:18:36 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/27 18:57:40 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	assign_arg(t_data *data, char *input, int len, int arg_i)
{
	int		i;
	int		j;
	char	quote;

	data->args[arg_i].s = (char *)malloc(sizeof(char) * len);
	if (!data->args[arg_i].s)
		return ;
	i = 0;
	j = 0;
	while (input[i])
	{
		quote = input[i];
		if (input[i] == '\'' || input[i] == '\"')
		{
			while (input[++i] && input[i] != quote)
			{
				if (input[i] == '$')
					i += handle_env_var(data, &input[i], arg_i, quote, j);
				else
					data->args[arg_i].s[j++] = input[i];
			}
			if (is_space(input[++i]))
				break ;
		}
		if ()
		{
			while (input[++i] && input[i] != '\'' && input[i] != '\"')
			{
				if (input[i] == '$')
					i += handle_env_var(data, &input[i], arg_i, '\0', j);
				else
					data->args[arg_i].s[j++] = input[i];
			}
			if (is_space(input[++i]))
				break ;
		}
	}
}

static int	calc_env_var_len(t_data *data, char *input, char quote, int *len)
{
	int		i;
	char	*key;
	char	*val;

	i = 0;
	if (quote == '\'')
		return (++i);
	if ((input[i] <= '9' && input[i] >= '0') || input[i] == '#')
	{
		if (input[i] == '0')
			*len += ft_strlen(data->program_name);
		if (input[i] == '#')
			*len += 1;
		return (++i);
	}
	while ((input[i] >= 'A' && input[i] <= 'Z') || \
	(input[i] >= 'a' && input[i] <= 'z') || \
	(input[i] >= '0' && input[i] <= '9') || input[i] == '_')
		i++;
	key = ft_substr(&input[i], 0, i);
	val = get_env_val(data, key);
	free(key);
	*len += ft_strlen(val);
	return (i);
}

static int	calc_arg_len(t_data *data, char *input, int *len_ptr)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	while (input[i])
	{
		quote = input[i];
		if (quote == '\'' || quote == '\"')
			while (input[++i] && input[i] != quote && len++)
				if (input[i] == '$')
					i += calc_env_var_len(data, &input[i], quote, &len);
		if (is_space(input[++i]))
			break ;
		if (input[i] != '\'' && input[i] != '\"')
			while (input[++i] && input[i] != '\'' && input[i] != '\"' && len++)
				if (input[i] == '$')
					i += calc_env_var_len(data, &input[i], '\0', &len);
		if (is_space(input[++i]))
			break ;
	}
	*len_ptr = len;
	return (i);
}

int	parser(t_data *data)
{
	int		i;
	int		j;
	int		len;
	int		arg_i;

	data->arg_count = count_args(data->input, data);
	data->args = malloc(sizeof(char *) * (data->arg_count + 1));
	if (!data->args)
		return (1);
	i = 0;
	len = 0;
	arg_i = 0;
	while (data->input[i])
	{
		while (data->input[i] && is_space(data->input[i]))
			i++;
		if (data->input[i])
		{
			j = calc_arg_len(data, &data->input[i], &len);
			assign_arg(data, &data->input[i], len, arg_i);
			arg_i++;
			i += j;
		}
	}
	return (0);
}
