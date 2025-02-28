/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_step.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:11:00 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/28 14:39:59 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	rm_quote_prompt(t_prompt_info *data)
{
	int	i;

	i = 0;
	while (data->prompt[i])
	{
		data->prompt[i] = rm_quote(data->prompt[i]);
		if (!data->prompt[i])
		{
			ft_freesplit(data->prompt, i);
			data->prompt = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	which_builtins(t_prompt_info *data)
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
		ft_exit(data);
	else
	{
		if (!rm_quote_prompt(data))
			return (0);
		if (extern_exec(data) == 0)
			return (0);
	}
	return (1);
}

int	last_step(char **str, t_prompt_info *data)
{
	fprintf(stderr, "here\n");
	if (only_space(*str))
		return (1);
	data->prompt = split_wquote(*str, ' ');
	if (!data->prompt)
		return (0);
	if (!(!ft_strncmp(data->prompt[0], "echo", 4)))
		*str = rm_quote(*str);
	if (!(*str))
		return (0);
	if (only_space(*str))
		return (1);
	if (!is_valid_cmd(*str, data))
		return (0);
	if (!check_builtins(data->prompt))
		return (0);
	else
	{
		fprintf(stderr, "here 1\n");
 		if (which_builtins(data) == 0)
			return (0);
	}
	return (1);
}
