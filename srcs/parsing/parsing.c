/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/27 11:39:07 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	which_builtins(char **prompt, char *str, char ***env)
{
	if (!ft_strncmp(prompt[0], "echo", 4))
		ft_echo(str);
	else if (!ft_strncmp(prompt[0], "cd", 2))
		ft_cd(prompt);
	else if (!ft_strncmp(prompt[0], "pwd", 3))
		ft_pwd(prompt);
	else if (!ft_strncmp(prompt[0], "export", 6))
		ft_export(prompt, env);
	if (!ft_strncmp(prompt[0], "unset", 5))
		*env = ft_unset(env, prompt, 1);
	else if (!ft_strncmp(prompt[0], "env", 3))
		ft_env(*env);
	else if (!ft_strncmp(prompt[0], "exit", 4))
		ft_exit(prompt[1], str, prompt, env);
	/*else if (!ft_strncmp(prompt[0], "<", 1)) // !!! Ne pas mettre dans builtins
		ft_quote();
	else if (!ft_strncmp(prompt[0], ">", 4)) // !!! Ne pas mettre dans builtins
		ft_unquote();
	else
		other_cmd();*/
}

int parsing(char *str, char ***env)
{
	char	**prompt;
	char	**pipe_prompt;

	pipe_prompt = NULL;
	if (is_pipe(str))
	{
		pipe_prompt = ft_splitpipe(str, '|');
		if (!pipe_prompt)
			return (0);
		for (int i = 0; i < 2; i++)
			printf("%s\n", pipe_prompt[i]);
	}
	prompt = split_wquote(str, ' ');
	if (!prompt)
		return (0);
	if (!check_builtins(prompt))
		return (freesplit(prompt), 1);
 	which_builtins(prompt, str, env);
	free(str);
	freesplit(prompt);
	if (pipe_prompt)
		freesplit(pipe_prompt);
	return (1);
}
