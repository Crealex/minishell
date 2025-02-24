/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:08:52 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/24 11:09:33 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirection_pipe(t_prompt_info *data)
{
	int	i;
	int	redirect;

	i = 0;
	data->fd_in = ft_calloc(data->pipe_len, sizeof(int));
	data->fd_out = ft_calloc(data->pipe_len, sizeof(int));
	if (!data->fd_in || !data->fd_out)
		return (0);
	while (data->pipe[i])
	{
		redirect = redirection(data, &data->pipe[i], i);
		if (redirect == 0)
			return (0);
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
	data->pipe = dollar_pipe(data->pipe, data->env);
	if (!data->pipe)
		return (0);
	data->pipe_len = len_double_tab(data->pipe);
	if (data->pipe_len < 0)
		return (0);
	if (redirection_pipe(data) == 0)
		return (0);
	return (1);
}