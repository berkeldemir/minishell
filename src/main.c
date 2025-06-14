/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:57:15 by beldemir          #+#    #+#             */
/*   Updated: 2025/06/14 19:08:51 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	*str[5] = {"echo", "-n", "-n","tibet", "berk"};

	

	data = malloc(sizeof(t_data));
	data->args = str;
	if (!data)
	{
		return (1);	
	}
	data->envp = envp;
	ft_echo(data);
	return (0);
}
