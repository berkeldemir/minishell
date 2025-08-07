/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:07:00 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/07 12:18:31 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_code(char c, int value)
{
	static int	code = 0;

	if (c == GET)
	{
		(void)value;
		return (code);
	}
	else if (c == SET)
		code = value;
	return (0);
}
