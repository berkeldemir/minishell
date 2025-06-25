/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:34:14 by beldemir          #+#    #+#             */
/*   Updated: 2025/06/25 17:10:07 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir_pipe(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	count_handle_redir_pipe(char *input, int *count)
{
	int	i;

	i = 0;
	if (!is_redir_pipe(input[0]))
		return (0);
	if ((input[i] == '>' && input[i + 1] == '>') || \
	(input[i] == '<' && input[i + 1] == '<'))
		i++;
	i++;
	*count += 1;
	while (is_space(input[i]))
		i++;
	return (i);
}
