/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:22:40 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/05 23:01:25 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	export_write(t_data *data)
{
	t_env	*tmp;
	t_env	**array;
	int		size;
	int		i;

	size = 0;
	tmp = data->env;
	while (tmp && ++size)
		tmp = tmp->next;
	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return ;
	tmp = data->env;
	i = 0;
	while (i < size)
	{
		array[i++] = tmp;
		tmp = tmp->next;
	}
	alpha_sort(array, size);
	i = -1;
	while (++i < size)
	{
		if (array[i]->value)
			printf("declare -x %s=\"%s\"\n", array[i]->key, array[i]->value);
		else
			printf("declare -x %s\n", array[i]->key);
	}
	free(array);
}

/*static char	*export_strdup(char *s)
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
}*/

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
	int	i;
	int	status;
	char	*key;
	char	*value;
	t_env	*tmp;

	i = 0;
	status = 0;
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write(2, " not a valid identifier\n", 24);
			status = 1;
			continue;
		}
	}
	if (!args[1])
		return (export_write(data), 0);
	i = 0;
	while (args[++i])
	{
		key = extract_key(args[i]);
		if (ft_strchr(args[i], '='))
			value = extract_value(args[i]);
		else
			value = NULL;
		tmp = data->env;
		while (tmp && ft_strcmp(tmp->key, key))
			tmp = tmp->next;
		if (tmp)
		{
			if (value)
				free(tmp->value);
			tmp->value = ft_strdup(value);
		}
		else
			env_add_back(&data->env, env_new(key, value));
	}
	return (status);
}
