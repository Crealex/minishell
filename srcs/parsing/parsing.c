/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/26 10:37:53 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int	redirect_nopipe(t_prompt_info *data)
{
	int		redirect;

	data->fd_in = ft_calloc(1, sizeof(int));
	if (!data->fd_in)
		return (0);
	data->fd_out = ft_calloc(1, sizeof(int));
	if (!data->fd_out)
		return (0);
	redirect = redirection(data, &data->str_prt, 0);
	if (redirect == 0)
		return (0);
	else if (redirect == 2)
		make_redirect(data);
	return (1);
}

int parsing(t_prompt_info *data)
{
	int		temp_fd[2];

	data->pipe = NULL;
	data->prompt = NULL;
	data->pipe_len = 0;
	data->fd_in = NULL;
	data->fd_out = NULL;
	data->is_pipe = is_pipe(&data->str_prt);
	if (data->is_pipe == -1)
		return (cleanup(data), 1);
	temp_fd[0] = dup(STDIN_FILENO);
	temp_fd[1] = dup(STDOUT_FILENO);
	if (data->is_pipe == 1)
	{
		if (!handle_pipe(data) || !exec_pipe(data, temp_fd))
			return (cleanup(data), 1);
	}
	else if (data->is_pipe == 0)
	{
		data->pipe_len = 1;
		if (!redirect_nopipe(data))
			return (cleanup(data), 1);
		if (!exec_no_pipe(data, temp_fd))
			return (cleanup(data), 1);
	}
	dup2(temp_fd[0], STDIN_FILENO);
	dup2(temp_fd[1], STDOUT_FILENO);
	end_redirect(data, temp_fd);
	return (cleanup(data), 1);
}
