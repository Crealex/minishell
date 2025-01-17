/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/17 22:11:15 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int parsing(char *str)
{
	//(void)str;
	char **prompt;

	prompt = ft_split(str, ' ');
 	if (!ft_strncmp(prompt[0], "echo", 4))
		provisory_start_echo(str); //ft_echo(prompt);
	/* else if (!ft_strncmp(prompt[0], "cd", 2))
		ft_cd();
	else if (!ft_strncmp(prompt[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(prompt[0], "export", 6))
		ft_export();
	else if (!ft_strncmp(prompt[0], "unset", 5))
		ft_unset();
	else if (!ft_strncmp(prompt[0], "env", 3))
		ft_env();*/
	else if (!ft_strncmp(prompt[0], "exit", 4))
		exit(0);/*
	else if (!ft_strncmp(prompt[0], "<", 1)) // !!! Ne pas mettre dans builtins
		ft_quote();
	else if (!ft_strncmp(prompt[0], ">", 4)) // !!! Ne pas mettre dans builtins
		ft_unquote();
	else
		other_cmd(); */
	return (1);
}
