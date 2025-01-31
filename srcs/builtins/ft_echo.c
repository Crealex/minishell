/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:42:41 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/31 10:32:01 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_flags(char *prompt)
{
	int i;
	int countn;

	i = 0;
	countn = 0;
	while (prompt[i] && (prompt[i] == '-' || prompt[i] == ' ' || prompt[i] == 'n'))
	{
		if (prompt[i] == '-')
		{
			if (i > 0 && prompt[i - 1] && prompt[i - 1] != ' ')
				return (countn);
			i++;
			if (prompt[i] != 'n')
				return (countn);
		}
		i++;
		if (prompt[i] == ' ' || !prompt[i])
			countn = i + 1;
	}
	update_exit_code(18);
	return (countn);
}

void	ft_echo(char *str, char **env)
{
	char *prompt;
	char *res;
	int n;

	prompt = ft_substr(str, 5, ft_strlen(str));
	n = 0;
	if (prompt[0] == '-')
	{
		n = handle_flags(prompt);
		res = ft_substr(prompt, n, ft_strlen(prompt));
		free(prompt);
		prompt = handle_dollars(res, env);
		free(res);
		printf("%s", prompt);
		free(prompt);
		if (!n)
			printf("\n");
	}
	else
	{
		res = handle_dollars(prompt, env);
		free(prompt);
		printf("%s\n", res);
		free(res);
	}
}


