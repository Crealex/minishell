/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:02:53 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/24 11:04:11 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_pipe(t_prompt_info *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_len)
	{
		if (data->fd_in[i] > 2)
			dup2(data->fd_in[i], STDIN_FILENO);
		if (data->fd_out[i] > 2)
			dup2(data->fd_out[i], STDOUT_FILENO);
		i++;
	}
}

void		make_redirect(t_prompt_info *data)
{
	if (data->is_pipe == 0)
	{
		if (data->fd_in[0] > 2)
			dup2(data->fd_in[0], STDIN_FILENO);
		if (data->fd_out[0] > 2)
			dup2(data->fd_out[0], STDOUT_FILENO);
	}
	else
		redirect_pipe(data);
}

void	end_redirect(t_prompt_info *data, int temp_fd_in, int temp_fd_out)
{
	int	i;

	i = 0;
	if (data->fd_in[0] > 2)
		dup2(temp_fd_in, STDIN_FILENO);
	if (data->fd_out[0] > 2)
		dup2(temp_fd_out, STDOUT_FILENO);
	if (data->is_pipe == 1)
	{
		while (data->pipe[i])
		{
			if (data->fd_in[i] > 2)
				close(data->fd_in[i]);
			if (data->fd_out[i] > 2)
				close(data->fd_out[i]);
			i++;
		}
	}
	close(temp_fd_in);
	close(temp_fd_out);
}
