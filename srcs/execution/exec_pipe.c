/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:57:04 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/24 15:33:05 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <bits/pthreadtypes.h>
#include <sys/wait.h>
#include <unistd.h>

static int	redirect_pipe(t_prompt_info *data, int i, int (*pipefd)[2])
{
	if (i < 0)
		return (0);
	if (data->fd_in[i] > 2)
		dup2(data->fd_in[i], STDIN_FILENO);
	if (data->fd_out[i] > 2)
		dup2(data->fd_out[i], STDOUT_FILENO);
	if (i < data->pipe_len - 1)
	{
		if (data->fd_out[i] < 2)
			dup2(pipefd[i][1], STDOUT_FILENO);
		close(pipefd[i][1]);
		close(pipefd[i][0]);
	}
	if (i > 0)
	{
		if (data->fd_in[i] < 2)
			dup2(pipefd[i - 1][0], STDIN_FILENO);
		close(pipefd[i - 1][0]);
		close(pipefd[i - 1][1]);
		while (i - 2 >= 0)
		{
			close(pipefd[i - 2][0]);
			close(pipefd[i - 2][1]);
			i--;
		}
	}
	return (1);
}

int	exec_pipe(t_prompt_info  *data, int temp_fd[2])
{
	int	pid;
	int	i;
	int	exit_status;
	int	(*pipefd)[2];

	i = 0;
	pipefd = ft_calloc(data->pipe_len - 1, sizeof(int *));
	if (!pipefd)
		return (0);
	while (data->pipe[i])
	{
		data->pos_pipe = i;
		if (i < data->pipe_len - 1)
			pipe(pipefd[i]);
		pid = fork();
		if (pid > 0)
		{
			if (i < data->pipe_len - 1)
				close(pipefd[i][1]);
			if (i > 0)
				close(pipefd[i - 1][0]);
		}
		if (pid == 0)
		{
			redirect_pipe(data, i, pipefd);
			free(pipefd);
			if (!last_step(&data->pipe[i], data, temp_fd))
				exit (0);
			end_redirect(data, temp_fd);
			cleanup(data);
			if (data->env)
				freesplit(data->env);
			exit (1);
		}
		waitpid(pid, &exit_status, 0);
		i++;
	}
	update_exit_code(WEXITSTATUS(exit_status));
	return (free(pipefd), 1);
}
