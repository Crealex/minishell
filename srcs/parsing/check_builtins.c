/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:25:02 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/06 16:00:52 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_echo_not_valid(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '-')
		if (cmd[1] != 'n')
			return (1);
	return (0);
}

static int	is_cd_not_valid(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '-')
		return (1);
	if (cmd[0] == '~')
		if (cmd[1] == '-' || cmd[1] == '+')
			return (1);
	return (0);
}

static int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "pwd", 3) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "exit", 4))
		return (1);
	return (0);
}

int	check_builtins(char **prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (is_builtin(prompt[i]))
			if (prompt[i + 1] && prompt[i + 1][0] == '-')
				return (0);
		if (!ft_strncmp(prompt[i], "cd", 2))
			if (is_cd_not_valid(prompt[i + 1]))
				return (0);
		if (!ft_strncmp(prompt[i], "env", 3))
		{
			if (prompt[i + 1]
				&& (prompt[i + 1][0] == '-' || prompt[i + 1][0] == '$'))
				return (0);
		}
		if (!ft_strncmp(prompt[i], "echo", 4)) // a corriger car fait buguer echo
			if (is_echo_not_valid(prompt[i + 1]))
				return (1); // j'ai mis un provisoirement pour avoir le foncitonnement normal de echo
		i++;
	}
	return (1);
}