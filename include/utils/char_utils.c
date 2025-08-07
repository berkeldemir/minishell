/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:42:11 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/07 21:50:45 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_alnum(char c)
{
	if ((c >= 'a' && c <= 'z') || \
	(c >= 'A' && c <= 'Z') || \
	(c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	is_alpha(int i)
{
	if (('a' <= i && i <= 'z') || ('A' <= i && i <= 'Z'))
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || (!is_alpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!is_alnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
