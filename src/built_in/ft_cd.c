/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:20:44 by tmidik            #+#    #+#             */
/*   Updated: 2025/07/31 18:19:53 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_data *data, char **args)
{
	char	*path;

	if (!args[1])
	{
		path = get_env_val(data, ft_strdup("HOME"));
		if (!path)
			return (write(2, "cd: HOME not set\n", 17), 1);
	}
	else
		path = args[1];
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	return (0);
}
