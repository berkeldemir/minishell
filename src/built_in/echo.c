/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:12:45 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/14 19:08:54 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_n(char *arg)
{
	int		i;

	i = 2;
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_data *data)
{
	int		i;
	int		j;
	int		new_line;

	i = 1;
	new_line = 1;
	data->arg_count = 5;
	while (i < data->arg_count && is_valid_n(data->args[i]))
	{
		new_line = 0;
		i++;
	}
	while (i < data->arg_count)
	{
		j = -1;
		while (data->args[i][++j])
			write(STDOUT_FILENO, &data->args[i][j], 1);
		if (i + 1 < data->arg_count)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
