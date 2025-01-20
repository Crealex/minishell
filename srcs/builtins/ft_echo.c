/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:42:41 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/20 23:16:11 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_flags(char *prompt)
{
	//  a verif comment fonctionne bash avec les flags
	int i;
	char *res;

	i = 1;
	while (prompt[i] && prompt[i] != ' ')
	{
		if (prompt[i] != 'n')
			return (0);
		i++;
	}
	res = ft_substr(prompt, i, ft_strlen(prompt));
	free(prompt);
	prompt = handle_dollars(res);
	free(res);
	printf("%s", prompt);
	free(prompt);
	return (i);
}

void	ft_echo(char *str)
{
	char *prompt;
	char *res;

	prompt = ft_substr(str, 5, ft_strlen(str));
	if (prompt[0] == '-')
	{
		if (!check_flags(prompt))
			printf("Invalid arguments\n");
	}
	else
	{
		res = handle_dollars(prompt);
		free(prompt);
		printf("%s\n", res);
		free(res);
	}
}


