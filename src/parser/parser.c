/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:18:36 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/20 19:56:59 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_quote(char *str)
{
	int		i;
	int		len;
	char	quote;
	int		quote_count;

	i = 0;
	len = 0;
	quote = str[0];
	quote_count = 1;
	while (str[++i] && !((str[i] == quote) && (quote_count % 2 == 1) && \
	(str[i + 1] == '\0' || str[i + 1] == ' ')))
	{
		len++;
		if (str[i] == quote)
			quote_count++;
		if (quote_count % 2 == 0 && str[i + 1] == ' ')
			break ;
	}
	return (len - quote_count + 1);
}

int	find_arg_len(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] && str[i] != '\'' && str[i] != '\"')
	{
		while (str[i] && !is_space(str[i]))
		{
			if (str[i] == '\'' || str[i] == '\"')
				break ;
			len++;
			i++;
		}
	}
	if (str[i] == '\'' || str[i] == '\"')
		len += handle_quote(&str[i]);
	return (len);
}

int	main(void)
{
	printf("%d\n", find_arg_len("aa\'DE\"N\"E'M'E\'M_a ikinciagruman"));
	return (0);
}
/*
int	ft_putarg(t_data *data, int arg_i)
{
	int	i;

	i = -1;
	while (data->input[++i])
	{
		data->args[arg_i].s[j] = data->input[i];
	}
	data->args[arg_i].index = arg_i;
}
*/

int	parser(t_data *data)
{
	int		i;
	int		arg_i;
	int		len;
	int		j;

	data->arg_count = count_args(data->input, data);
	j = -1;
	while (++j < data->arg_count)
		printf("%s\n", data->args[j].s);
	data->args = (t_args *)malloc(sizeof(t_args) * data->arg_count);
	if (!data->args)
		return (1);
	i = 0;
	arg_i = 0;
	while (data->input[i])
	{
		while (is_space(data->input[i]))
			i++;
		len = find_arg_len(&data->input[i]);
		data->args[arg_i].s = (char *)malloc(sizeof(char) * (len + 1));
		if (!data->args[arg_i].s)
			exit_freely(data);
		//i += ft_putarg(data, arg_i);
		arg_i++;
	}
	return (0);
}
