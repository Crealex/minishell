/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:08:52 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/21 17:15:51 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	is_child(int status)
{
	static int bool = 0;

	if (status == -1)
		return (bool);
	else
		bool = status;
	return (bool);
}

char *get_path(char *cmd)
{
	int i;
	char	*res;
	char	*cmd_path;
	char	**path;

	if (access(cmd, X_OK) != -1 && (cmd[0] == '/' || cmd[0] == '.'))
		return (ft_strdup(cmd));
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
	printf("res : %s\n", res);
	freesplit(path);
	free(cmd_path);
	return (res);
}

int	check_acces_file(char *cmd)
{
	char *file;
	struct stat statt;

	file = ft_substr(cmd, 2, ft_strlen(cmd));
	ft_bzero(&statt, sizeof(statt));
	stat(file, &statt);
	if (S_ISDIR(statt.st_mode) || ft_strlen(file) == 0)
	{
		print_error("minishell: ", cmd, ": Is a directory\n");
		update_exit_code(126);
		return (0);
	}
	if (access(file, X_OK) != -1)
		return (free(file), 1);
	if (access(file, F_OK) == -1)
	{
		print_error("minishell: ", cmd, ": No such file or directory\n");
		update_exit_code(127);
		free(file);
		return (0);
	}
	print_error("minishell: ", cmd, ": Permission denied\n");
	update_exit_code(126);
	return (0);
}

// static void	closing_pipe(t_prompt_info *data, int (*pipefd)[2])
// {
// 	int	i;

// 	i = data->pos_pipe;
// 	if (!pipefd)
// 		return ;
// 	if (i < data->pipe_len - 1)
// 	{
// 		fprintf(stderr, "closing pipe start < len max : %s\n", data->prompt[0]);
// 		if (data->fd_out[i] < 2)
// 			fprintf(stderr,"rest close %d\n", close(pipefd[i][1]));
// 	}
// 	if (i > 0)
// 	{
// 		fprintf(stderr, "closing pipe > 0 : %s\n", data->prompt[0]);
// 		if (data->fd_in[i] < 2)
// 		{
// 			fprintf(stderr, "closing pipefd[i- 1][0]\n");
// 			fprintf(stderr, "ret close : %d\n", close(pipefd[i - 1][0]));
// 		}
// 	}
// }

int	extern_exec(t_prompt_info *data)
{
	char	*path;
	int		exit_status;
	pid_t	pid;

	if (data->prompt[0] && ft_strlen(data->prompt[0]) > 2
		&& data->prompt[0][0] == '.' && data->prompt[0][1] == '/')
		{
			if (!check_acces_file(data->prompt[0]))
				return (0);
		}
	path = get_path(data->prompt[0]);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, data->prompt, data->env) == -1)
			return (printf("pas exec\n"), 0);
	}
	is_child(1);
	// fprintf(stderr, "before waitpid : %s\n", data->prompt[0]);
	waitpid(pid, &exit_status, 0);
	// fprintf(stderr, "end of process : %s\n", data->prompt[0]);
	is_child(0);
	free(path);
	update_exit_code(WEXITSTATUS(exit_status));
	return (1);
}
