/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:19:42 by beldemir          #+#    #+#             */
/*   Updated: 2025/06/14 21:48:39 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	prompt(t_data *data)
{
	//data->user = getenv("USER");
	while (1)
	{
		if (getcwd(data->currend_dir, sizeof(data->currend_dir)) == NULL)
			return ;
		printf("%s%s@:%s %s\n%s", GREEN, getenv("USER"), ORANGE, \
		data->currend_dir, DEFAULT);
		data->input = readline("\033[38;2;8;99;117m>₺ \033[0m");
		if (!data->input)
			break ;
		if (data->input[0] != '\0')
		{
			parser(data);
			execute(data);
		}
		free(data->input);
	}
}

void	wait_input(t_data *data)
{
	prompt(data);
}
