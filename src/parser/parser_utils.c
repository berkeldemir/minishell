/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:17:43 by tmidik            #+#    #+#             */
/*   Updated: 2025/05/12 19:55:55 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	count_handle_quote(char *str, int *count)
{
	int		i;
	char	quote;
	int		quote_count;

	i = 0;
	quote = str[i];
	quote_count = 1;
	while (!((str[++i] == quote) && (quote_count % 2 == 1) && \
	(str[i + 1] == '\0' || str[i + 1] == ' ')))
	{	
		if (str[i] == quote)
			quote_count++;
		if (str[i] == '\0')
			return (0);
	}
	*count++;
	return (++i);
}

int	count_args(char *str)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		while (is_space(str[i]))
			i++;
		if (str[i] && str[i] != '\'' && str[i] != '\"')
		{
			count++;
			while (str[i] && !is_space(str[i]) && \
			str[i] != '\"' && str[i] != '\'')
				i++;
		}
		if (str[i] == '\"' || str[i] == '\'')
			i += count_handle_quote(&str[i], &count);
		if (str[i] == '\"' || str[i] == '\'')
			exit_freely();
	}
	return (count);
}
