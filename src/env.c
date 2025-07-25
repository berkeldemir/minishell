/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:47:42 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/20 19:15:24 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*get_env_val(t_data *data, char *key)
{
	t_env	*tmp;

	tmp = *data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0 && \
		ft_strlen(key) == ft_strlen(tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*env_converter_helper(t_env *lst)
{
	char	*new;
	char	*ptr;
	char	*k;
	char	*v;

	k = lst->key;
	v = lst->value;
	new = malloc(ft_strlen(k) + ft_strlen(v) + 2);
	if (!new)
		return (NULL);
	ptr = new;
	while (*k)
		*new++ = *k++;
	*new++ = '=';
	while (*v)
		*new++ = *v++;
	*new = '\0';
	return (ptr);
}

char	**env_converter(t_data *data)
{
	size_t	i;
	t_env	*lst;
	size_t	size;
	char	**ret;

	size = 0;
	lst = *data->env;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	ret = (char **)malloc((sizeof(char *) * size) + 1);
	if (!ret)
		return (NULL);
	lst = *data->env;
	i = 0;
	while (i < size)
	{
		ret[i] = env_converter_helper(lst);
		lst = lst->next;
		i++;
	}
	return (ret);
}
