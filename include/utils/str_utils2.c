/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 20:03:53 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/08 11:13:55 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str, long *tab_num)
{
	int			i;
	int			sign;
	long		num;

	if (!str)
		return (-1);
	i = 0;
	num = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == 32 || (str[i] <= 13 && str[i] >= 9)))
		i++;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = -1;
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0')
	{
		num = (num * 10) + (str[i++] - 48);
		if (num > INT_MAX)
			return (-1);
	}
	if (str[i] != '\0' && !(str[i] == 32 || (str[i] <= 13 && str[i] >= 9)))
		return (-2);
	if (tab_num)
		*tab_num = num * sign;
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	while (*s != c && *s != 0)
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen((char *)s);
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

int	safe_strlen(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str)
		free(str);
	return (len);
}
