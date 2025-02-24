/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:02:53 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/24 15:31:46 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		make_redirect(t_prompt_info *data)
{
	if (data->is_pipe == 0)
	{
		if (data->fd_in[0] > 2)
			dup2(data->fd_in[0], STDIN_FILENO);
		if (data->fd_out[0] > 2)
			dup2(data->fd_out[0], STDOUT_FILENO);
	}
}

void	end_redirect(t_prompt_info *data, int *temp_fd)
{
	int	i;

	i = 0;
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
	close(temp_fd[0]);
	close(temp_fd[1]);
}
