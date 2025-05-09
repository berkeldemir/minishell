/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:18:36 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/09 18:47:22 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	lexer(t_data *data)
{
	int		i;
	int		arg_i;
	int		len;
	int		word_count;

	i = 0;
	arg_i = 0;
	word_count = count_words(data->input);
	data->args = malloc(sizeof(char *) * (word_count + 1));
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

int	parser(t_data *data)
{
	lexer(data);
	return (0);
}
