/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/04 14:13:02 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	which_builtins(t_prompt_info *data)
{
	if (!ft_strncmp(data->prompt[0], "echo", 4))
		ft_echo(data->str_prt);
	else if (!ft_strncmp(data->prompt[0], "cd", 2))
		ft_cd(data->prompt, &data->env);
	else if (!ft_strncmp(data->prompt[0], "pwd", 3))
		ft_pwd(data->prompt);
	else if (!ft_strncmp(data->prompt[0], "export", 6))
		ft_export(data->prompt, &data->env);
	if (!ft_strncmp(data->prompt[0], "unset", 5))
		data->env = ft_unset(&data->env, data->prompt, 1);
	else if (!ft_strncmp(data->prompt[0], "env", 3))
		ft_env(data->env);
	else if (!ft_strncmp(data->prompt[0], "exit", 4))
		ft_exit(data->prompt[1], data->str_prt, data->prompt, &data->env);
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

static int	last_step(char *str, char ***env, t_prompt_info *data)
{
	data->str_prt = ft_strdup(str);
	data->prompt = split_wquote(str, ' ');
	data->env = cpy_double_array(data->env, *env);
	if (!data->prompt)
		return (0);
	if (!check_builtins(data->prompt))
		return (freesplit(data->prompt), 1);
 	which_builtins(data);
	free(str);
	free(data->str_prt);
	freesplit(data->prompt);
	if (data->is_pipe == 1)
		freesplit(data->pipe);
	return (1);
}

int parsing(char *str, char ***env)
{
	t_prompt_info	data;
	int ip;

	data.pipe = NULL;
	data.is_pipe = is_pipe(&str);
	ip = 0;
	if (data.is_pipe == 1)
	{
		data.pipe = ft_splitpipe(str, '|');
		if (!data.pipe)
			return (0);
		data.pipe = dollar_pipe(data.pipe, *env);
		if (!data.pipe)
			return (0);
	}
	else if (data.is_pipe == 0)
		str = handle_dollars(str, *env);
	else
		return (0);
	//printf("redirection : %i\n", redirection(&str, &data));
	if (!is_valid_cmd(data.pipe, str))
		return (1);
	if (data.is_pipe == 1)
	{
		while (data.pipe[ip])
		{
			if (!last_step(data.pipe[ip++], env, &data))
				return (0);
		}
	}
	else
	{
		if (!last_step(str, env, &data))
			return (0);
	}
	return (1);
}
