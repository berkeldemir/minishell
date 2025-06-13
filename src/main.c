/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:57:15 by beldemir          #+#    #+#             */
/*   Updated: 2025/06/14 00:34:04 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	init_program(t_data *data, int ac, char **av, char **envp)
{
	int	i;

	if (ac != 1)
		return (1);
	data->program_name = ft_strdup(av[0]);
	i = -1;
	while (envp[++i])
		i++;
	data->env = (char **)malloc(i + 1);
	if (!data->env)
		return (1);
	i = -1;
	while (envp[++i])
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = NULL;
	return (0);
}

static int	parser_tester(t_data *data)
{
	int	i;

	printf("%s%s@:%s deneme\n%s", GREEN, getenv("USER"), ORANGE, DEFAULT);
	data->input = readline("\033[38;2;8;99;117m>₺ \033[0m");
	if (!data->input)
		return (0);
	parser(data);
	i = -1;
	while (++i < data->arg_count)
		printf("%s\n", data->args[i].s);
	free(data->input);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ac != 1)
		return (1);
	init_program(data, ac, av, envp);

	// PARSER TESTER
	parser_tester(data);
	// PARSER TESTER
}/*
	wait_input(data);
	parser(data);
	int i = -1;
	while (++i < data->arg_count)
		printf("%s\n", data->args[i]);
	return (0);
}*/