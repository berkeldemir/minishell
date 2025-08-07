/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:22:40 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/07 13:48:02 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	export_write(t_data *data, t_env *tmp, int i)
{
	t_env	**array;

	data->tmps.len = 0;
	while (tmp && ++data->tmps.len)
		tmp = tmp->next;
	array = malloc(sizeof(t_env *) * data->tmps.len);
	if (!array)
		return ;
	tmp = data->env;
	while (i < data->tmps.len)
	{
		array[i++] = tmp;
		tmp = tmp->next;
	}
	alpha_sort(array, data->tmps.len);
	i = -1;
	while (++i < data->tmps.len)
	{
		if (array[i]->value)
			printf("declare -x %s=\"%s\"\n", array[i]->key, array[i]->value);
		else
			printf("declare -x %s\n", array[i]->key);
	}
	free(array);
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

static void export_setter(t_data *data, char **args, int i)
{
	char	*key;
	char	*value;
	t_env	*tmp;

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
		safe_free((void **)&tmp->value);
		tmp->value = value;
		free(key);
	}
	else
		env_add_back(&data->env, env_new(key, value));
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	t_env	*tmp;

	exit_code(SET, 0);
	tmp = data->env;
	if (!args[1])
		return (export_write(data, tmp, 0), 0);
	i = 0;
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write(2, "export: not a valid identifier\n", 31);
			exit_code(SET, 1);
			continue ;
		}
	}
	i = 0;
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]))
			continue ;
		export_setter(data, args, i);
	}
	return (exit_code(GET, 0));
}
