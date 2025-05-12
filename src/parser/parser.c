/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:18:36 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/12 18:44:13 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_vars_and_quotes(t_data *data)
{
	char	*new;

	while (data->input)
	handle_vars(data);
}

int	parser(t_data *data)
{
	int		i;
	int		arg_i;
	int		len;

	i = 0;
	arg_i = 0;
	data->arg_count = count_args(data->input);
	data->args = (char **)malloc(sizeof(char *) * (data->arg_count + 1));
	if (!data->args)
		return (1);
	while (data->input[i])
	{
		while (data->input[i] && is_space(data->input[i]))
			i++;
		if (data->input[i] && !is_space(data->input[i]))
		{
			len = word_len(&data->input[i]);
			data->args[arg_i] = ft_strndup(&data->input[i], len);
			arg_i++;
			i += len;
		}
	}
	data->args[arg_i] = NULL;
	return (handle_vars_and_quotes(data));
}
