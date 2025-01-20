/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/15 15:09:59y dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	which_builtins(char **prompt, char *str, char ***env)
{
	/*if (!ft_strncmp(prompt[0], "echo", 4))
		ft_echo();
	else if (!ft_strncmp(prompt[0], "cd", 2))
		ft_cd();
	else if (!ft_strncmp(prompt[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(prompt[0], "export", 6))
		ft_export();*/
	if (!ft_strncmp(prompt[0], "unset", 5))
		*env = ft_unset(env, prompt, 1);
	else if (!ft_strncmp(prompt[0], "env", 3))
	{
		
		ft_env(*env);
	}
	else if (!ft_strncmp(prompt[0], "exit", 4))
		ft_exit(prompt[1], str, prompt);
	int i = 0;
	while ((*env)[i])
	{
		printf("%s\n", (*env)[i]);
		i++;
	}
	/*else if (!ft_strncmp(prompt[0], "<", 1)) // !!! Ne pas mettre dans builtins
		ft_quote();
	else if (!ft_strncmp(prompt[0], ">", 4)) // !!! Ne pas mettre dans builtins
		ft_unquote();
	else
		other_cmd();*/
}

int parsing(char *str, char **env)
{
	char **prompt;

	if (!str || !ft_strncmp(str, "\0", 1))
		return (0);
	prompt = ft_split(str, ' ');
	if (!prompt)
		return (1);
	if (!check_prompt(prompt))
		return (freesplit(prompt), 1);
 	which_builtins(prompt, str, &env);
	printf("---------------------------------------------------------------\n");
	int i = 0;
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	return (0);
}
