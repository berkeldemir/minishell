/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:17:43 by tmidik            #+#    #+#             */
/*   Updated: 2025/05/30 19:36:57 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	put_value_in_place(t_data *data, char *str, int j)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[++i])
	{
		data->args[data->tmps.arg_i].s[j] = str[i];
		j++;
		i++;
	}
	if (str)
		free(str);
	return (i);
}

char	*get_env_val(t_data *data, char *key)
{
	int				i;
	char			*ptr;
	unsigned int	key_lenght;

	i = 0;
	ptr = NULL;
	key_lenght = ft_strlen(key);
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], key, key_lenght) && \
		data->env[i][key_lenght] == '=')
			ptr = &data->env[i][key_lenght + 1];
		i++;
	}
	if (key)
		free(key);
	return (ptr);
}

static int	count_handle_quote(t_data *data, char *str, int *count)
{
	int		i;
	char	quote;
	int		quote_count;

	i = 0;
	quote = str[i];
	quote_count = 1;
	while (str[++i] && !((str[i] == quote) && (quote_count % 2 == 1) && \
	(str[i + 1] == '\0' || is_space(str[i + 1]))))
	{	
		if (str[i] == quote)
			quote_count++;
		if (str[i] == '\0')
			exit_freely(data);
		if (quote_count % 2 == 0 && str[i + 1] == ' ')
			break ;
	}
	*count += 1;
	return (++i);
}

int	count_args(char *str, t_data *data)
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
			while (str[i] && !is_space(str[i]))
				i++;
		}
		if (str[i] == '\'' || str[i] == '\"')
			i += count_handle_quote(data, &str[i], &count);
		if (!str[i])
			break ;
	}
	return (count);
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

