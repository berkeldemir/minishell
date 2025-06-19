/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:22:40 by tmidik            #+#    #+#             */
/*   Updated: 2025/06/19 16:41:10 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*export_strdup(char *s)
{
	int		i;
	char	*toreturn;

	i = -1;
	toreturn = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!toreturn)
		return (NULL);
	while (s[++i] != '\0')
		toreturn[i] = s[i];
	toreturn[i] = '\0';
	return (toreturn);
}

static char	*extract_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static char	*extract_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	j = 0;
	value = (char *)malloc(sizeof(char) * (ft_strlen(str + i) + 1));
	if (!value)
		return (NULL);
	while (str[i] != '\0')
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

int	ft_export(t_data *data, char **args)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	key = extract_key(args[1]);
	value = extract_value(args[1]);
	tmp = *data->env;

	while (tmp)
	{
		if (ms_ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = export_strdup(value);
			free(key);
			free(value);
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = env_new(key, value);
	env_add_back(data->env, tmp);
	return (0);
}