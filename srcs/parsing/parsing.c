/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/07 15:02:11 by atomasi          ###   ########.fr       */
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
	else if (!ft_strncmp(data->prompt[0], "unset", 5))
		data->env = ft_unset(&data->env, data->prompt, 1);
	else if (!ft_strncmp(data->prompt[0], "env", 3))
		ft_env(data->env);
	else if (!ft_strncmp(data->prompt[0], "exit", 4))
		ft_exit(data->prompt[1], data->str_prt, data->prompt, &data->env);
	else
		extern_exec(data);
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
	res[i] = NULL;
	return (res);
}

int	only_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	last_step(char *str, t_prompt_info *data)
{
	if (only_space(str))
		return (1);
	data->prompt = split_wquote(str, ' ');
	if (!data->prompt)
		return (0);
	if (!check_builtins(data->prompt))
		return (freesplit(data->prompt), 1);
	else
 		which_builtins(data);
	free(data->str_prt);
	freesplit(data->prompt);
	if (data->is_pipe == 1)
		freesplit(data->pipe);
	return (1);
}

int parsing(t_prompt_info *data)
{
	int ip;

	data->pipe = NULL;
	data->is_pipe = is_pipe(&data->str_prt);
	ip = 0;
	if (data->is_pipe == 1)
	{
		data->pipe = ft_splitpipe(data->str_prt, '|');
		if (!data->pipe)
			return (0);
		data->pipe = dollar_pipe(data->pipe, data->env);
		if (!data->pipe)
			return (0);
	}
	else if (data->is_pipe == 0)
		data->str_prt = handle_dollars(data->str_prt, data->env);
	else
		return (0);
	//printf("redirection : %i\n", redirection(&str, &data));
	if (!is_valid_cmd(data->pipe, data->str_prt))
		return (free(data->str_prt), 1);
	if (data->is_pipe == 1)
	{
		while (data->pipe[ip])
		{
			if (!last_step(data->pipe[ip++], data))
				return (0);
		}
	}
	else
	{
		if (!last_step(data->str_prt , data))
			return (0);
	}
	return (1);
}
