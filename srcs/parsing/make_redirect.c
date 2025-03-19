/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:16 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/19 13:42:22 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	make_redirect(t_prompt_info *data)
{
	if (data->fd_in[0] > 2)
		dup2(data->fd_in[0], STDIN_FILENO);
	if (data->fd_out[0] > 2)
		dup2(data->fd_out[0], STDOUT_FILENO);
}

void	end_redirect(t_prompt_info *data, int redirect)
{
	if (redirect)
	{
		dup2(data->temp_fdin, STDIN_FILENO);
		dup2(data->temp_fdout, STDOUT_FILENO);
	}
	close(data->temp_fdin);
	close(data->temp_fdout);
}
