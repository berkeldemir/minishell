/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 20:02:12 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/06 20:07:28 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_findsize(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
	{
		size++;
		n *= -1;
	}
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static char	*ft_writenum(char *ptr, int num, int size)
{
	int	sign;

	sign = 1;
	if (num < 0)
	{
		sign = -1;
		num = -num;
	}
	ptr[size] = '\0';
	while (size > 0)
	{
		ptr[--size] = (num % 10) + '0';
		num /= 10;
	}
	if (sign == -1)
		ptr[0] = '-';
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*new;
	int		size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_findsize(n);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	new = ft_writenum(new, n, size);
	return (new);
}
