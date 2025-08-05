/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:25:07 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/05 18:15:03 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_data *data, char **args)
{
	unsigned int	retval;

	retval = 0;
	if (args[1])
	{
		if (args[2])
			return (write(STDERR_FILENO, " too many arguments\n", 19), 1);
		if (ft_atoi(args[1], (long *)&retval) == -2)
			return (write(STDERR_FILENO, " numeric argument required\n", 26), 2);
		if (data->cmd_count != 1)
			safe_quit(data, NULL, 0);
		write(STDOUT_FILENO, "exit\n", 5);
		safe_quit(data, NULL, 0);
		exit(retval % 256);
	}
	safe_quit(data, NULL, 0);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(0);
}
