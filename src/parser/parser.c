/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:18:36 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/12 22:00:58 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_vars_and_quotes(t_data *data)
{
	char	*new;

	while (data->input)
	handle_vars(data);
}

int	find_arg_len(char *str)
{
	int	len;

	len = ft_strlen(str);
	// BURADA KALDIM!
	// TIRNAKLARA VE GLOBAL DEĞİŞKENLERE GÖRE İŞLEM YAPILACAK
	// TEK BAŞINA TEK TIRNAK ('') İÇİNE YAZILAN HER ŞEY OLDUĞU GİBİ KALIR
	// ÇİFT TIRNAK İÇİNDE TEK TIRNAK İÇİNE YAZILANLAR İSE ÖNEMSİZDİR, TIRNAKLAR DAHİ ALINIR.
	// ÇİFT TIRNAK İÇİNE ÇİFT TIRNAK İÇİNDE YAZILANLAR TIRNAKLAR OLMADAN ALINIR.
	// BLA BLA BİSSÜRÜ KURAL.
}

int	parser(t_data *data)
{
	int		i;
	int		arg_i;
	int		len;

	i = 0;
	arg_i = 0;
	data->arg_count = count_args(data->input);
	data->args = (char **)malloc(sizeof(char *) * (data->arg_count + 1));
	if (!data->args)
		return (1);
	while (data->input[i])
	{
		while (is_space(str[i]))
			i++;
		len = find_arg_len(&data->input[i]);
		data->args[arg_i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!data->args[arg_i])
			exit_freely(data);
		i += ft_putarg(data, data->args[arg_i]);
		arg_i++;
	}
	data->args[arg_i] = NULL;
	return (0);
}
