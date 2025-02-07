/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:08:52 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/07 10:59:20 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

char *get_path(char *cmd)
{
	int i;
	char	*res;
	char	*cmd_path;
	char	**path;

	if (access(cmd, X_OK) != -1)
		return ( cmd);
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

int	check_acces_file(char *cmd)
{
	char *file;
	struct stat statt;

	file = ft_substr(cmd, 2, ft_strlen(cmd));
	stat(file, &statt);
	if (S_ISDIR(statt.st_mode))
	{
		printf("minishell: %s: Is a directory\n", cmd);
		update_exit_code(126);
		return (0);
	}
	if (access(file, X_OK) != -1)
		return (free(file), 1);
	if (access(file, F_OK) == -1)
	{
		printf("minishell: %s: No such file or diretory\n", cmd);
		update_exit_code(127);
		free(file);
		return (0);
	}
	printf("minishell: %s: Permission denied\n", cmd);
	update_exit_code(126);
	return (0);
}

void	extern_exec(t_prompt_info *data)
{
	char	*path;
	int		exit_status;
	pid_t	pid;

	if (data->prompt[0] && ft_strlen(data->prompt[0]) > 2
		&& data->prompt[0][0] == '.' && data->prompt[0][1] == '/')
		{
			if (!check_acces_file(data->prompt[0]))
				return ;
		}
	path = get_path(data->prompt[0]);
	pid = fork();
	if (pid == 0)
		execve(path, data->prompt, data->env);
	waitpid(pid, &exit_status, 0);
	update_exit_code(WEXITSTATUS(exit_status));
}
