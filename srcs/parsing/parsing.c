/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/03 16:34:55 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	which_builtins(char **prompt, char *str, char ***env)
{
	if (!ft_strncmp(prompt[0], "echo", 4))
		ft_echo(str);
	else if (!ft_strncmp(prompt[0], "cd", 2))
		ft_cd(prompt, env);
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

static char	**dollar_pipe(char **pipe_prompt, char **env)
{
	int	i;
	char **res;

	i = 0;
	while (pipe_prompt[i])
		i++;
	res = ft_calloc(i + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (pipe_prompt[i])
	{
		res[i] = handle_dollars(pipe_prompt[i], env);
		if (!res[i])
			return (ft_freesplit(res, i), NULL);
		i++;
	}
	free(pipe_prompt);
	res[i] = '\0';
	return (res);
}

int parsing(char *str, char ***env)
{
	char			**prompt;
	char			**pipe_prompt;
	t_prompt_info	data;

	pipe_prompt = NULL;
	data.is_pipe = is_pipe(&str);
	if (data.is_pipe == 1)
	{
		pipe_prompt = ft_splitpipe(str, '|');
		if (!pipe_prompt)
			return (0);
		pipe_prompt = dollar_pipe(pipe_prompt, *env);
		if (!pipe_prompt)
			return (0);
	}
	else if (data.is_pipe == 0)
		str = handle_dollars(str, *env);
	else
		return (0);
	//printf("redirection : %i\n", redirection(&str, &data));
	if (!is_valid_cmd(pipe_prompt, str))
		return (0);
	// tout ce qu'il y a ci-dessous sera dans une autre fonction
	prompt = split_wquote(str, ' ');
	if (!prompt)
		return (0);
	if (!check_builtins(prompt))
		return (freesplit(prompt), 1);
 	which_builtins(prompt, str, env); // remplacer par une fonction input_valid? et appeler which builtins depuis celle-ci
	free(str);
	freesplit(prompt);
	if (pipe_prompt)
		freesplit(pipe_prompt);
	return (1);
}
