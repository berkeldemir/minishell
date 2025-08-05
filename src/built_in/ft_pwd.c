/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:35:20 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/05 17:43:13 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_data *data)
{
	if (getcwd(data->cwd, sizeof(data->cwd)))
		printf("%s\n", data->cwd);
	else
		perror("pwd");
	return (0);
}
