/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:02:53 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/20 15:27:52 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		make_redirect(t_prompt_info *data, int *temp_fd_in, int *temp_fd_out)
{
	if (data->fd_in > 2)
	{
		*temp_fd_in = dup(STDIN_FILENO);
		dup2(data->fd_in, STDIN_FILENO);
	}
	if (data->fd_out > 2)
	{
		*temp_fd_out = dup(STDOUT_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
	}
}

void	end_redirect(t_prompt_info *data, int temp_fd_in, int temp_fd_out)
{
	if (data->fd_in > 2)
		dup2(temp_fd_in, STDIN_FILENO);
	if (data->fd_out > 2)
		dup2(temp_fd_out, STDOUT_FILENO);
}
