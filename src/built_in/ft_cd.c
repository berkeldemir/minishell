/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:20:44 by tmidik            #+#    #+#             */
/*   Updated: 2025/08/06 19:38:36 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	env_update(t_env *env, char *key, char *value)
{
	t_env	*node;

	node = env;
	while (node)
	{
		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0)
		{
			free(node->value);
			node->value = ft_strdup(value);
			return ;
		}
		node = node->next;
	}
}

int	ft_cd(t_data *data, char **args)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	if (!getcwd(data->cwd, sizeof(data->cwd)))
		return (perror("getcwd"), 1);
	oldpwd = ft_strdup(data->cwd);
	if (!args[1])
	{
		path = get_env_val(data, ft_strdup("HOME"));
		if (!path)
			return (write(2, "cd: HOME not set\n", 17), free(oldpwd), 1);
	}
	else if (!args[2])
		path = args[1];
	else
		return (write(2, "cd: too many arguments\n", 20), free(oldpwd), 1);
	if (chdir(path) != 0)
		return (perror("cd"), free(oldpwd), 1);
	if (!getcwd(data->cwd, sizeof(data->cwd)))
		return (perror("getcwd"), free(oldpwd), 1);
	newpwd = ft_strdup(data->cwd);
	(env_update(data->env, "OLDPWD", oldpwd), free(oldpwd));
	(env_update(data->env, "PWD", newpwd), free(newpwd));
	return (0);
}
