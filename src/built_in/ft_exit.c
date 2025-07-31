/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:25:07 by tmidik            #+#    #+#             */
/*   Updated: 2025/07/31 13:31:33 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_data *data, char **args)
{
	int	retval;

	retval = 0;
	if (args[1])
	{
		if (args[2])
			return (printf("Only one argument is allowed.\n"), 1);
		if (ft_atoi(args[1], (unsigned long *)&retval) != 0)
			return (printf("Argument should be a number.\n"), 1);
		if (data->cmd_count != 1)
			safe_quit(data, NULL, 0);
		write(STDOUT_FILENO, "exit\n", 5);
		exit(retval % 256);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	exit(0);
}
