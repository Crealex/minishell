/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:36:30 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/19 13:51:15 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	double_close(int fd1, int fd2)
{
	if (fd1 > 2)
		close (fd1);
	if (fd2 > 2)
		close (fd2);
}

static int	first_step(t_prompt_info *data, int i)
{
	if (i < 0)
		return (0);
	if (data->fd_in[i] > 2)
		dup2(data->fd_in[i], STDIN_FILENO);
	if (data->fd_out[i] > 2)
		dup2(data->fd_out[i], STDOUT_FILENO);
	return (1);
}

int	redirect_pipe(t_prompt_info *data, int i, int (*pipefd)[2])
{
	int	legit_dup;

	legit_dup = 1;
	if (!first_step(data, i))
		return (0);
	if (i < data->pipe_len - 1)
	{
		if (data->fd_out[i] < 2)
		{
			if (data->fd_in[i + 1] > 2 && (ft_strncmp(data->pipe[i], "echo", 4)
					|| ft_strncmp(data->pipe[i], "env", 3)
					|| ft_strncmp(data->pipe[i], "export", 6)))
				legit_dup = 0;
			else
				dup2(pipefd[i][1], STDOUT_FILENO);
		}
		double_close(pipefd[i][0], pipefd[i][1]);
	}
	if (i > 0)
	{
		if (data->fd_in[i] < 2)
			dup2(pipefd[i - 1][0], STDIN_FILENO);
		close(pipefd[i - 1][0]);
	}
	return (legit_dup);
}
