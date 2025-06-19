/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:25:07 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/19 13:33:23 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char **args)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (args[1])
	{
		perror("exit: no arguments allowed!");
		return (1);
	}
	exit(0);
}