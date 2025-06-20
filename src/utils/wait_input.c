/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmidik <tibetmdk@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:19:42 by beldemir          #+#    #+#             */
/*   Updated: 2025/06/20 15:43:51 by tmidik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ms_ft_strdup(char *s)
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

static char	*get_display_path(char *path)
{
	char	*home;
	char	*result;

	home = getenv("HOME");
	if (home && strncmp(path, home, ms_ft_strlen(home)) == 0)
	{
		if (path[ms_ft_strlen(home)] == '\0')
			return (ms_ft_strdup("~"));
		result = ms_ft_strjoin(path + ms_ft_strlen(home), "~");
		return (result);
	}
	return (strdup(path));
}

static void	print_prompt(char *path)
{
	char	*display;

	display = get_display_path(path);
	printf("%s%s@:%s %s\n%s",
		GREEN, getenv("USER"), ORANGE, display, DEFAULT);
	free(display);
}

void	wait_input(t_data *data)
{
	char	path[1023];

	while (1)
	{
		if (getcwd(path, sizeof(path)) == NULL)
			return ;
		print_prompt(path);
		data->input = readline("\033[38;2;8;99;117m>₺ \033[0m");
		if (!data->input)
			break ;
		if (data->input[0] != '\0')
		{
			parser(data);
			execute(data);
		}
		free(data->input);
	}
}
