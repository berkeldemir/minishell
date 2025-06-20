/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:25:07 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/20 16:53:51 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char **args)
{
	if (args[1])
	{
		write(2, "exit: no arguments allowed\n", 27);
		return (1);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	exit(0);
}
