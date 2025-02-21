/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:57:04 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/21 16:26:55 by dvauthey         ###   ########.fr       */
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
	if (i < data->pipe_len - 1)
	{
		fprintf(stderr, "redirect firsts\n");
		if (data->fd_out[i] < 2)
			dup2(pipefd[i][1], STDOUT_FILENO);
		close(pipefd[i][1]);
		close(pipefd[i][0]);
	}
	if (i > 0)
	{
		fprintf(stderr, "redirect lasts\n");
		fprintf(stderr, "pipefd[i - 1][0] : %d, pipefd[i - 1][1] : %d\n", pipefd[i - 1][0], pipefd[i - 1][1]);
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

static int	closing_all_pipes(t_prompt_info *data, int (*pipefd)[2])
{
	int	i;

	i = 0;
	while (i < data->pipe_len - 1)
	{
		if (close(pipefd[i][0]) == -1)
			return (0);
		if (close(pipefd[i][1]) == -1)
			return (0);
		i++;
	}
	return (1);
}

int	exec_pipe(t_prompt_info  *data)
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
		printf("pipefd[%d][0] : %d, pipefd[%d][1] : %d\n", i, pipefd[i][0], i, pipefd[i][1]);
		pid = fork();
		if (pid == 0)
		{
			fprintf(stderr, "-----------------------------------------\n");
			fprintf(stderr, "in child fork\n");
			redirect_pipe(data, i, pipefd);
			fprintf(stderr, "in child fork, after redirect\n");
			if (!last_step(&data->pipe[i], data, pipefd))
				exit (0);
			fprintf(stderr, "in child fork, after last step\n");
			exit (1);
		}
		waitpid(pid, &exit_status, 0);
		i++;
	}
	update_exit_code(WEXITSTATUS(exit_status));
	if (closing_all_pipes(data, pipefd) == 0)
		return (free(pipefd), 0);
	return (free(pipefd), 1);
}
