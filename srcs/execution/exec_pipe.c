/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:57:04 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/19 13:55:05 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clean_exec_pipe(t_prompt_info *data)
{
	cleanup(data, 0);
	if (data->env)
		freesplit(data->env);
}

static void	close_parent(int i, t_prompt_info *data, int (*pifd)[2])
{
	if (i < data->pipe_len - 1)
		close(pifd[i][1]);
	if (i > 0)
		close(pifd[i - 1][0]);
}

static void	fork_handler(t_prompt_info *data, int i, pid_t *pid, int (*pifd)[2])
{
	if (i < data->pipe_len - 1)
		pipe(pifd[i]);
	pid[i] = fork();
	if (pid[i] > 0)
	{
		close_parent(i, data, pifd);
	}
	if (pid[i] == 0)
	{
		close(data->fd_history);
		free(pid);
		if (!redirect_pipe(data, i, pifd))
		{
			free(pifd);
			clean_exec_pipe(data);
			exit (update_exit_code(-1));
		}
		free(pifd);
		if (data->redirection[i] == 1)
			last_step(&data->pipe[i], data);
		clean_exec_pipe(data);
		exit (update_exit_code(-1));
	}
}

int	exec_pipe(t_prompt_info *data)
{
	pid_t	*pid;
	int		i;
	int		exit_status;
	int		(*pipefd)[2];

	i = 0;
	pipefd = ft_calloc(data->pipe_len - 1, sizeof(int *));
	if (!pipefd)
		return (0);
	pid = ft_calloc(data->pipe_len, sizeof(pid_t));
	if (!pid)
		return (free(pipefd), 0);
	while (data->pipe[i])
	{
		data->pos_pipe = i;
		fork_handler(data, i, pid, pipefd);
		i++;
	}
	i = 0;
	is_child(1);
	while (i < data->pipe_len)
		waitpid(pid[i++], &exit_status, 0);
	is_child(0);
	update_exit_code(WEXITSTATUS(exit_status));
	return (free(pipefd), free(pid), 1);
}
