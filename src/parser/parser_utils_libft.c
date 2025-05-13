/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_libft.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:41:04 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/13 15:02:56 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*new;
	size_t	i;


	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		new = (char *)malloc(sizeof(char) * 1);
		if (!new)
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	if (len > slen - start)
		len = slen - start;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}
