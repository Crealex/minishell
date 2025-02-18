/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:37:07 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/18 16:57:42 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	pipe_handler(t_prompt_info *data, int pipefd[2])
{
	int	i;

	i = data->pos_pipe;
	printf("i : %i\n", i);
	if (i < 0)
		return ;
	if (i == 0)
	{
		printf("help\n");
		printf("ret dup2 out : %i\n", dup2(pipefd[1], STDOUT_FILENO));
	}
	else if (i == data->pipe_len - 1)
	{
		dup2(pipefd[0], STDIN_FILENO);
		printf("endddd\n");
   	}
	else
	{
		printf("middle\n");
		dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
	}
}

void	dup_fd_start(t_prompt_info *data, int *fd_in,
	int *fd_out, int pipefd[2])
{
	if (data->fd_in > 2 || data->is_pipe == 1)
		*fd_in = dup(STDIN_FILENO);
	if (data->fd_out > 2 || data->is_pipe == 1)
		*fd_out = dup(STDOUT_FILENO);
	if (data->fd_in > 2)
		if (data->is_pipe == 0 || data->pos_pipe == 0)
			dup2(data->fd_in, STDIN_FILENO);
	if (data->fd_out > 2)
		if (data->is_pipe == 0 || data->pos_pipe == data->pipe_len - 1)
			dup2(data->fd_out, STDOUT_FILENO);
	if (data->is_pipe == 1)
		pipe_handler(data, pipefd);
}

void	dup_fd_end(t_prompt_info *data, int *fd_in, int *fd_out)
{
		if (data->fd_in > 2)
			dup2(*fd_in, STDIN_FILENO);
		if (data->fd_out > 2)
			dup2(*fd_out, STDOUT_FILENO);
}
