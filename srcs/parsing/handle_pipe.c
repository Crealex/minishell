/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:08:52 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/21 17:10:42 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirection_pipe(t_prompt_info *data, int *tp_fdin, int *tp_fdout)
{
	int	i;
	int	j;
	int	redirect;

	i = 0;
	j = 0;
	data->fd_in = ft_calloc(data->pipe_len, sizeof(int));
	data->fd_out = ft_calloc(data->pipe_len, sizeof(int));
	if (!data->fd_in || !data->fd_out)
		return (0);
	while (data->pipe[i])
	{
		redirect = redirection(data, &data->pipe[i], i);
		if (redirect == 0)
			return (0);
		else if (redirect == 2 && j == 0)
		{
			*tp_fdin = dup(STDIN_FILENO);
			*tp_fdout = dup(STDOUT_FILENO);
			j++;
		}
		i++;
	}
	make_redirect(data);
	return (1);
}

int	handle_pipe(t_prompt_info *data, int *temp_fdin, int *temp_fdout)
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
	if (redirection_pipe(data, temp_fdin, temp_fdout) == 0)
		return (0);
	return (1);
}