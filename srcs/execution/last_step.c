/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_step.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:11:00 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/03 15:09:54 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	which_builtins(t_prompt_info *data)
{
	//data->prompt[0] = rm_quote(data->prompt[0]);
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
		ft_exit(data);
	else
	{
		if (extern_exec(data) == 0)
			return (0);
	}
	return (1);
}

int	last_step(char **str, t_prompt_info *data) // uniquement pour pipe
{
	data->prompt = split_wquote(*str, ' ');
	if (!data->prompt || !data->prompt[0])
		return (0);
	if (!handle_quote(data))
		return (0);
	if (only_space(data->prompt))
		return (0);
	if (!is_valid_cmd(*str, data))
		return (0);
	if (!check_builtins(data->prompt))
	 	return (0);
	else
	{
		if (which_builtins(data) == 0)
			return (0);
	}
	return (1);
}
