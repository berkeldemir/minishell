/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:20:44 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/18 17:09:12 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_data *data, char **args)
{
	char    *path;
    char    cwd[4096];

	if (!args[1]) // cd komutuna argüman yoksa
    {
        path = getenv("HOME");
        if (!path)
        {
            return (write(2, "cd: HOME not set\n", 17), 1);
        }
    }
    else
    {
        path = args[1];
    }
	
	if (chdir(path) != 0)
    {
        perror("cd");
        return (1);
    }
	return (0);
}