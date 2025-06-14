/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:17:43 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/14 17:39:36 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

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
/*
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
*/

int	count_helper(char *input, int *count)
{
	int	i;

	i = 0;
	while (is_space(input[i]))
		i++;
	if (input[i])
		*count += 1;
	return (i);
}

int	count_args(char *input, t_data *data)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (input[i])
	{
		data->tmps.quote = input[i];
		if (is_quote(data->tmps.quote) && ++i)
			while (input[i] && input[i] != data->tmps.quote)
				i++;
		if (is_quote(input[i]) && is_space(input[++i]))
			i += count_helper(&input[i], &count);
		if (input[i] && !is_quote(input[i]))
			while (input[i] && !is_quote(input[i]) && !is_space(input[i]))
				++i;
		if (is_space(input[i]) && i++)
			i += count_helper(&input[i], &count);
		if (!input[i])
		{
			count++;
			break ;
		}
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

