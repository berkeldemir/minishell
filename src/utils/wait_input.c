/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:19:42 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/06 11:41:23 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	prompt(t_data *data)
{
	char	path[1023];

	//data->user = getenv("USER");
	while (1)
	{
		if (getcwd(path, sizeof(path)) == NULL)
			return ;
		printf("%s%s@:%s %s\n%s", GREEN, getenv("USER"), ORANGE, path, DEFAULT);
		data->input = readline("\033[38;2;8;99;117m>₺ \033[0m");
		if (!data->input)
			break ;
	}
}

void wait_input(t_data *data)
{
    prompt(data);
    
}
