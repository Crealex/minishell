/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:21:45 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/19 10:45:31 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	is_file(char *cmd)
{
	if (ft_strlen(cmd) > 2)
	{
		if (cmd[0] == '.' && cmd[1] == '/')
			return (1);
		else if (cmd[0] == '/')
			return (1);
	}
	return (0);
}

char	*extract_name_cmd(char *prompt)
{
	int		i;
	int		space;
	int		ires;
	char	*res;

	i = 0;
	space = 0;
	ires = 0;
	while (prompt[space] && ft_isspace(prompt[space]))
		space++;
	while (prompt[i + space] && !ft_isspace(prompt[i + space]))
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = space;
	while (prompt[i] && !ft_isspace(prompt[i]))
	{
		res[ires] = prompt[i];
		ires++;
		i++;
	}
	res[ires] = '\0';
	return (res);
}

int	check_valid_builtins(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 5) || !ft_strncmp("echo ", cmd, 5))
		return (1);
	else if (!ft_strncmp("cd", cmd, 3) || !ft_strncmp("cd ", cmd, 3))
		return (1);
	else if (!ft_strncmp("pwd", cmd, 4) || !ft_strncmp("pwd ", cmd, 4))
		return (1);
	else if (!ft_strncmp("export", cmd, 7) || !ft_strncmp("export ", cmd, 7))
		return (1);
	else if (!ft_strncmp("unset", cmd, 6) || !ft_strncmp("unset ", cmd, 6))
		return (1);
	else if (!ft_strncmp("env", cmd, 4) || !ft_strncmp("env ", cmd, 4))
		return (1);
	else if (!ft_strncmp("exit", cmd, 5) || !ft_strncmp("exit ", cmd, 5))
		return (1);
	return (0);
}

int	check_validity(char *cmd, int tok, char **env)
{
	char	**path;
	char	*abs_path;
	char	*cmd_path;
	int		i;

	if (check_valid_builtins(cmd) == 1 && tok == 0)
		return (1);
	if (is_file(cmd) == 1)
		return (1);
	else if (ft_strlen(cmd) <= 2 && cmd[0] == '.' && cmd[1] != '/')
		return (0);
	path = get_all_path(env);
	if (!path || !*path)
		return (update_exit_code(127), 0);
	i = 0;
	cmd_path = ft_strjoin("/", cmd);
	while (path[i])
	{
		abs_path = ft_strjoin(path[i], cmd_path);
		if (access(abs_path, X_OK) != -1)
			return (freesplit(path), free(abs_path), free(cmd_path), 1);
		free(abs_path);
		i++;
	}
	return (freesplit(path), free(cmd_path), update_exit_code(127), 0);
}

int	is_valid_cmd(char *str, t_prompt_info *data)
{
	char	*cmd_name;
	int		res;

	res = 0;
	if (str)
	{
		if (is_quote(data->prompt[0]) && !check_valid_builtins(str))
		{
			data->prompt[0] = rm_quote(data->prompt[0]);
			print_err(data->prompt[0], ": command not found\n", NULL);
			return (update_exit_code(127), 0);
		}
		cmd_name = extract_name_cmd(str);
		res = check_validity(cmd_name, 0, data->env);
		if (res == 0)
			print_err(cmd_name, ": command not found\n", NULL);
		free(cmd_name);
		return (res);
	}
	return (res);
}
