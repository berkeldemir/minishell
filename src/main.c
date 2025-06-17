/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:57:15 by beldemir          #+#    #+#             */
/*   Updated: 2025/06/17 17:14:53 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	init_program(t_data *data, int ac, char **av, char **envp)
{
	int		i;
	char	*key;
	char	*val;
	t_env	*node;

	if (ac != 1)
		return (1);
	data->program_name = ft_strdup(av[0]);
	data->env = (t_env **)malloc(sizeof(t_env *));
	if (!data->env)
		return (1);
	data->env[0] = NULL;
	i = -1;
	while (envp[++i])
	{
		key = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		val = ft_substr(envp[i], ft_strchr(envp[i], '=') - envp[i] + 1, \
		ft_strlen(envp[i]));
		node = env_new(key, val);
		env_add_back(data->env, node);
	}
	return (0);
}

/*static int	parser_tester(t_data *data)
{
	int	i;
	t_env	*ptr;

	ptr = *data->env;
	while (ptr)
	{
		printf("%s = %s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
	printf("-----------------------");
	char	**e = env_converter(data);
	i = -1;
	while (e[++i])
		printf("%s\n", e[i]);
	printf("%s%s@:%s deneme\n%s", GREEN, getenv("USER"), ORANGE, DEFAULT);
	data->input = readline("\033[38;2;8;99;117m>₺ \033[0m");
	if (!data->input)
		return (0);
	parser(data);
	i = -1;
	while (++i < data->arg_count)
		printf("%s$\n", data->args[i].s);
	free(data->input);
	return (0);
}*/

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ac != 1)
		return (1);
	init_program(data, ac, av, envp);
	wait_input(data);
}