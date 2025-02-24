/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_step.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:11:00 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/24 16:18:56 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	which_builtins(t_prompt_info *data, int temp_fd[2])
{
	if (!ft_strncmp(data->prompt[0], "echo", 4))
		ft_echo(data->str_prt, data);
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
		ft_exit(data, temp_fd);
	else
		if (extern_exec(data, temp_fd) == 0)
			return (0);
	return (1);
}

int	last_step(char **str, t_prompt_info *data, int temp_fd[2])
{
	if (only_space(*str))
		return (1);
	data->prompt = split_wquote(*str, ' ');
	if (!data->prompt)
		return (0);
	*str = rm_quote(*str);
	if (!(*str))
		return (0);
	if (!is_valid_cmd(*str))
		return (1);
	if (!check_builtins(data->prompt))
		return (1);
	else
 		if (which_builtins(data, temp_fd) == 0)
			return (0);
	return (1);
}