/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:30:03 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/14 19:06:05 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
		data->redirection[i] = no_redirection(data, &data->pipe[i]);
		if (data->redirection[i] == 0)
		{
			if (!pre_redirect(data, &data->pipe[i], i))
				return (0);
			data->redirection[i] = redirection(data, &data->pipe[i], i);
			if (data->redirection[i] == 0)
				return (0);
		}
		i++;
	}
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
