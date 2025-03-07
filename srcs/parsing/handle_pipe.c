/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:08:52 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/06 14:45:43 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirection_pipe(t_prompt_info *data)
{
	int	i;
	
	i = 0;
	data->fd_in = ft_calloc(data->pipe_len, sizeof(int));
	if (!data->fd_in)
		return (0);
	data->fd_out = ft_calloc(data->pipe_len, sizeof(int));
	if (!data->fd_out)
		return (0);
	data->redirection = ft_calloc(data->pipe_len, sizeof(int));
	if (!data->redirection)
		return (0);
	while (data->pipe[i])
	{
		data->redirection[i] = redirection(data, &data->pipe[i], i);
		i++;
	}
	make_redirect(data);
	return (1);
}

int	handle_pipe(t_prompt_info *data)
{
	data->pos_pipe = -1;
	data->pipe = ft_splitpipe(data->str_prt, '|');
	if (!data->pipe)
		return (0);
	data->pipe = dollar_pipe(data->pipe, data);
	if (!data->pipe)
		return (0);
	data->pipe_len = len_double_tab(data->pipe);
	if (data->pipe_len < 0)
		return (0);
	if (redirection_pipe(data) == 0)
		return (0);
	return (1);
}
