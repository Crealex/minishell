/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:42:41 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/17 22:01:36 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	provisory_start_echo(char *str)
{
	char *prompt;
	char *res;

	prompt = ft_substr(str, 5, ft_strlen(str));
	if (prompt[0] == '-')
	{
		if (prompt[1] == 'n')
		{
			res = ft_substr(prompt, 2, ft_strlen(prompt));
			prompt = check_dollars(res);
			printf("%s", prompt);
		}
		else
			printf("No valid arguments\n");
		return ;
	}
	else
	{
		res = check_dollars(prompt);
		printf("%s\n", res);
	}
}
/*
static void print_args(char **prompt, int s)
{
	char *to_print;

	//printf(" test print_args: %s\n", prompt[s]);
	to_print = parse_prompt(prompt, s);
	ft_putstr_fd(to_print, 1);
}

void	ft_echo(char **prompt)
{
	if (!prompt[1])
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (prompt[1][0] == '-' && prompt[1][1] == 'n')
	{
		if (prompt[2])
			print_args(prompt, 2);
		else
			ft_putstr_fd("\n", 1);
		return ;
	}
	//printf("test ft_echo\n");
	print_args(prompt, 1);
	ft_putchar_fd('\n', 0);
}*/


