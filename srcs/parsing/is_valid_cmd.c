/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:21:45 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/03 16:40:41 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **get_all_path() // segfault dans cette fonction
{
	char *path_str;
	char **res;

	path_str = getenv("PATH");
	if (!path_str)
		return (NULL);
	res = ft_split(path_str, ':');
	if (!res)
		return (NULL);
	free(path_str);
	return (res);
}

char	*extract_name(char *prompt)
{
	int i;
	int ires;
	char *res;

	i = 0;
	ires = 0;
	while (prompt[i] && prompt[i] != ' ')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (prompt[i] && prompt[i] != ' ')
	{
		res[ires] = prompt[i];
		ires++;
		i++;
	}
	return (res);
}

int check_validity(char *cmd)
{
	char **path;
	char *abs_path;
	char *cmd_path;
	int i;

	if (ft_strncmp("echo", cmd, 4) == 0 || ft_strncmp("cd", cmd, 2) == 0
		|| ft_strncmp("pwd", cmd, 3) == 0 || ft_strncmp("export", cmd, 6) == 0
		|| ft_strncmp("unset", cmd, 5) == 0 || ft_strncmp("env", cmd, 3) == 0
		|| ft_strncmp("exit", cmd, 4) == 0)
		return (1);
	path = get_all_path();
	i = 0;
	printf("all path : %s\n", path[i]);
	cmd_path = ft_strjoin(cmd, "/");
	while (path[i])
	{
		abs_path = ft_strjoin(path[i], cmd_path);
		if (access(abs_path, X_OK) != -1)
			return (freesplit(path), free(abs_path), free(cmd_path) , 1);
		free(abs_path);
		i++;
	}
	freesplit(path);
	free(cmd_path);
	return (0);
}

int	is_valid_cmd(char **prompt, char *prompt_str)
{
	char *cmd_name;
	int res;
	int i;

	if (!prompt && prompt_str)
	{
		cmd_name = extract_name(prompt_str);
		res = check_validity(cmd_name);
		if (res == 0)
			printf("%s: command not found\n", cmd_name);
		free(cmd_name);
		return (res);
	}
	i = 0;
	while (prompt && prompt[i])
	{
		cmd_name = extract_name(prompt[i]);
		res = check_validity(cmd_name);
		free(cmd_name);
		if (res == 0)
			return (printf("%s: command not found\n", cmd_name), 0);
		i++;
	}
	return (res);
}
