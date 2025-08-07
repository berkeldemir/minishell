/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:16:21 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/07 21:27:13 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data	*env_data(char c, t_data *data)
{
	static t_data	*ret;

	if (c == SET)
		ret = data;
	else
		return (ret);
	return (NULL);
}
