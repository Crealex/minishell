/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/21 17:13:07 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int parsing(char *str)
{
	//(void)str;
	char **prompt;

	prompt = ft_split(str, ' ');
 	if (!ft_strncmp(prompt[0], "echo", 4))
		ft_echo(str); //ft_echo(prompt);
	else if (!ft_strncmp(prompt[0], "cd", 2))
		ft_cd(prompt);
	else if (!ft_strncmp(prompt[0], "pwd", 3))
		ft_pwd(prompt);
	/*else if (!ft_strncmp(prompt[0], "export", 6))
		ft_export();
	else if (!ft_strncmp(prompt[0], "unset", 5))
		ft_unset();
	else if (!ft_strncmp(prompt[0], "env", 3))
		ft_env();*/
	else if (!ft_strncmp(prompt[0], "exit", 4))
		ft_exit(prompt[1], str, prompt);

		/*
	else if (!ft_strncmp(prompt[0], "<", 1)) // !!! Ne pas mettre dans builtins
		ft_quote();
	else if (!ft_strncmp(prompt[0], ">", 4)) // !!! Ne pas mettre dans builtins
		ft_unquote();
	else
		other_cmd(); */
	free(str);
	freesplit(prompt);
	return (1);
}
