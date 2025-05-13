/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:33:03 by tmidik            #+#    #+#             */
/*   Updated: 2025/05/13 19:46:01 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	s_word_len(char *s, char c)
{
	size_t	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	free_all(char **words, size_t count)
{
	size_t	i = 0;
	while (i < count)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

static size_t	s_count_words(char *s, char c)
{
	size_t	count = 0;
	int		in_word = 0;

	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	char	**words;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	words = malloc(sizeof(char *) * (s_count_words(s, c) + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (*s && i < s_count_words(s, c))
	{
		while (*s == c)
			s++;
		len = s_word_len(s, c);
		words[i] = malloc(len + 1);
		if (!words[i])
			return (free_all(words, i), NULL);
		words[i][len] = '\0';
		while (len--)
			words[i][len] = s[len];
		s += s_word_len(s, c);
		i++;
	}
	words[i] = NULL;
	return (words);
}

void	free_array(char **array)
{
	int	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
