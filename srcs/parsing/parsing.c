/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/10 11:35:53 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


static int	redirect_nopipe(t_prompt_info *data)
{
	data->fd_in = ft_calloc(1, sizeof(int));
	if (!data->fd_in)
		return (0);
	data->fd_out = ft_calloc(1, sizeof(int));
	if (!data->fd_out)
		return (0);
	data->redirection = ft_calloc(1, sizeof(int));
	if (!data->redirection)
		return (0);
	data->redirection[0] = redirection(data, &data->str_prt, 0);
	if (data->redirection[0] != 1)
		return (0);
	else
		make_redirect(data);
	return (1);
}

static int	parsing_no_pipe(t_prompt_info *data)
{
	if (!redirect_nopipe(data))
		return (0);
	data->str_prt = expansion(data->str_prt, data);
	if (!data->str_prt)
		return (0);
	return (1);
}
static void	init_data(t_prompt_info *data)
{
	data->temp_fdin = dup(STDIN_FILENO);
	data->temp_fdout = dup(STDOUT_FILENO);
	data->pipe = NULL;
	data->prompt = NULL;
	data->pipe_len = 0;
	data->fd_in = NULL;
	data->fd_out = NULL;
	data->is_pipe = -1;
	data->redirection = NULL;
}


int	parsing(t_prompt_info *data)
{
	init_data(data);
	data->is_pipe = is_pipe(&data->str_prt);
	if (data->is_pipe == -1)
		return (cleanup(data, 0), 1);
	if (data->is_pipe == 1)
	{
		if (!handle_pipe(data) || !exec_pipe(data))
			return (cleanup(data, 1), 1);
	}
	else if (data->is_pipe == 0)
	{
		data->pipe_len = 1;
		if (!parsing_no_pipe(data))
			return (cleanup(data, 1), 1);
		if (!exec_no_pipe(data))
			return (cleanup(data, 1), 1);
	}
	return (cleanup(data, 1), 1);
}
