/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:18:36 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/12 12:54:46 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parser(t_data *data)
{
	int		i;
	int		arg_i;
	int		len;

	i = 0;
	arg_i = 0;
	data->arg_count = count_words(data->input);
	data->args = malloc(sizeof(char *) * (data->arg_count + 1));
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
	return (0);
}
