/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:08:52 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/06 14:05:08 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char *get_path(char *cmd)
{
	int i;
	char	*res;
	char	*cmd_path;
	char	**path;

	path = get_all_path();
	i = 0;
	cmd_path = ft_strjoin("/", cmd);
	while (path[i])
	{
		res = ft_strjoin(path[i], cmd_path);
		if (access(res, X_OK) != -1)
			return (freesplit(path), free(cmd_path), res);
		free(res);
		i++;
	}
	freesplit(path);
	free(cmd_path);
	return (res);
}

void	extern_exec(t_prompt_info *data)
{
	char *path;
	pid_t pid;

	path = get_path(data->prompt[0]);
	pid = fork();
	if (pid == 0)
		execve(path, data->prompt, data->env);
	wait(NULL);
}