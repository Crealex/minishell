/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:02:53 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/28 11:50:46 by atomasi          ###   ########.fr       */
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

void	end_redirect(t_prompt_info *data, int redirect)
{
	int	i;

	i = 0;
	if (redirect)
	{
		dup2(data->temp_fdin, STDIN_FILENO);
		dup2(data->temp_fdout, STDOUT_FILENO);
	}
	close(data->temp_fdin);
	close(data->temp_fdout);
}
